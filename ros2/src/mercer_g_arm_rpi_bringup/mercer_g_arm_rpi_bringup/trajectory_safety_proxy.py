#!/usr/bin/env python3
import time
from enum import Enum

import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer, ActionClient, GoalResponse, CancelResponse
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import Bool, Empty
from std_srvs.srv import Trigger

from control_msgs.action import FollowJointTrajectory


class SafetyState(Enum):
    DISABLED = 0
    ENABLED = 1
    FAULT = 2


class TrajectorySafetyProxy(Node):
    """
    Action-only safety gate for JointTrajectoryController.

    Upstream (safe) action server:
      /arm_controller_safe/follow_joint_trajectory

    Downstream (real) action client:
      /arm_controller/follow_joint_trajectory
    """

    def __init__(self):
        super().__init__('trajectory_safety_proxy')

        self.cb_group = ReentrantCallbackGroup()

        # Parameters
        self.declare_parameter('controller_name', 'arm_controller')
        self.declare_parameter('heartbeat_timeout_s', 0.5)

        controller = self.get_parameter('controller_name').get_parameter_value().string_value
        self.heartbeat_timeout_s = self.get_parameter('heartbeat_timeout_s').value

        self.downstream_action = f'/{controller}/follow_joint_trajectory'
        self.upstream_action = f'/{controller}_safe/follow_joint_trajectory'

        # State
        self.state = SafetyState.DISABLED
        self.fault_reason = ''
        self.enable_motion = False
        self.estop = False
        self.last_heartbeat = 0.0

        # Track active downstream goal
        self._downstream_goal_handle = None
        self._active_upstream_goal_handle = None

        # Subscriptions
        self.create_subscription(Bool, '/enable_motion', self._on_enable, 10)
        self.create_subscription(Bool, '/estop', self._on_estop, 10)
        self.create_subscription(Empty, '/heartbeat', self._on_heartbeat, 10)

        # Fault reset service
        self.create_service(Trigger, '/reset_fault', self._on_reset_fault)

        # Action server (safe)
        self._action_server = ActionServer(
            self,
            FollowJointTrajectory,
            self.upstream_action,
            execute_callback=self._execute_cb,
            goal_callback=self._goal_cb,
            cancel_callback=self._cancel_cb,
            callback_group=self.cb_group
        )

        # Action client (real controller)
        self._action_client = ActionClient(
            self,
            FollowJointTrajectory,
            self.downstream_action,
            callback_group=self.cb_group
        )

        # Watchdog timer
        self.create_timer(0.05, self._watchdog)  # 20 Hz

        self.get_logger().info(f"Upstream(safe): {self.upstream_action}")
        self.get_logger().info(f"Downstream(real): {self.downstream_action}")
        self.get_logger().info("Default state: DISABLED (motion not permitted)")

    # ---------------- Inputs ----------------
    def _on_enable(self, msg: Bool):
        self.enable_motion = bool(msg.data)
        if not self.enable_motion and self.state == SafetyState.ENABLED:
            self._transition_to_disabled("operator disabled motion")

    def _on_estop(self, msg: Bool):
        self.estop = bool(msg.data)
        if self.estop:
            self._enter_fault("ESTOP asserted")

    def _on_heartbeat(self, _msg: Empty):
        self.last_heartbeat = time.time()

    def _on_reset_fault(self, _req, _resp):
        if self.state != SafetyState.FAULT:
            _resp.success = True
            _resp.message = "No fault latched."
            return _resp

        if self.estop:
            _resp.success = False
            _resp.message = "Cannot reset fault while ESTOP is asserted."
            return _resp

        self.state = SafetyState.DISABLED
        self.fault_reason = ''
        _resp.success = True
        _resp.message = "Fault cleared; state is DISABLED."
        self.get_logger().warn("Fault reset; now DISABLED.")
        return _resp

    # ---------------- State machine ----------------
    def _watchdog(self):
        # Heartbeat check
        hb_age = time.time() - self.last_heartbeat if self.last_heartbeat > 0 else float('inf')
        heartbeat_ok = hb_age < self.heartbeat_timeout_s

        if self.state == SafetyState.ENABLED:
            if not heartbeat_ok:
                self._enter_fault(f"Heartbeat lost (age={hb_age:.3f}s)")
            if self.estop:
                self._enter_fault("ESTOP asserted")

        if self.state == SafetyState.DISABLED:
            # Auto-enable only if all conditions OK (optional; you can require explicit reset-only)
            if self.enable_motion and (not self.estop) and heartbeat_ok:
                self.state = SafetyState.ENABLED
                self.get_logger().info("State -> ENABLED (motion permitted)")

    def _enter_fault(self, reason: str):
        if self.state == SafetyState.FAULT:
            return
        self.state = SafetyState.FAULT
        self.fault_reason = reason
        self.get_logger().error(f"State -> FAULT: {reason}")
        self._cancel_downstream_goal()

    def _transition_to_disabled(self, reason: str):
        self.state = SafetyState.DISABLED
        self.get_logger().warn(f"State -> DISABLED: {reason}")
        self._cancel_downstream_goal()

    # ---------------- Action server callbacks ----------------
    def _goal_cb(self, goal_request: FollowJointTrajectory.Goal):
        if self.state != SafetyState.ENABLED:
            self.get_logger().warn(
                f"Rejecting goal: state={self.state.name}, reason={self.fault_reason or 'not enabled'}"
            )
            return GoalResponse.REJECT

        if not self._action_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().error("Downstream action server not available; rejecting goal.")
            return GoalResponse.REJECT

        return GoalResponse.ACCEPT

    def _cancel_cb(self, goal_handle):
        # Allow upstream cancel; propagate downstream cancel when possible
        self.get_logger().warn("Upstream cancel requested.")
        self._cancel_downstream_goal()
        return CancelResponse.ACCEPT

    async def _execute_cb(self, goal_handle):
        # This executes after acceptance
        self._active_upstream_goal_handle = goal_handle

        # If we became unsafe after accept, abort
        if self.state != SafetyState.ENABLED:
            goal_handle.abort()
            result = FollowJointTrajectory.Result()
            result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
            result.error_string = f"Aborted: state={self.state.name}"
            return result

        # Forward to downstream
        downstream_goal = FollowJointTrajectory.Goal()
        downstream_goal.trajectory = goal_handle.request.trajectory
        downstream_goal.path_tolerance = goal_handle.request.path_tolerance
        downstream_goal.goal_tolerance = goal_handle.request.goal_tolerance
        downstream_goal.goal_time_tolerance = goal_handle.request.goal_time_tolerance

        send_future = self._action_client.send_goal_async(
            downstream_goal,
            feedback_callback=lambda fb: goal_handle.publish_feedback(fb.feedback)
        )
        downstream_handle = await send_future
        self._downstream_goal_handle = downstream_handle

        if not downstream_handle.accepted:
            goal_handle.abort()
            result = FollowJointTrajectory.Result()
            result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
            result.error_string = "Downstream controller rejected the goal."
            return result

        # Wait for result
        result_future = downstream_handle.get_result_async()
        downstream_result = await result_future

        # Map downstream result to upstream
        if goal_handle.is_cancel_requested:
            goal_handle.canceled()
        else:
            # If we faulted during execution, report abort
            if self.state == SafetyState.FAULT:
                goal_handle.abort()
            else:
                goal_handle.succeed()

        self._downstream_goal_handle = None
        self._active_upstream_goal_handle = None
        return downstream_result.result

    def _cancel_downstream_goal(self):
        if self._downstream_goal_handle is not None:
            try:
                self._downstream_goal_handle.cancel_goal_async()
            except Exception as e:
                self.get_logger().error(f"Failed to cancel downstream goal: {e}")


def main():
    rclpy.init()
    node = TrajectorySafetyProxy()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
