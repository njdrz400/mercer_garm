#!/usr/bin/env python3
import math
import time
from typing import Dict, List

import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from std_msgs.msg import Float64, Bool
from trajectory_msgs.msg import JointTrajectoryPoint
from control_msgs.action import FollowJointTrajectory

class TrajectoryBridge(Node):
    def __init__(self):
        super().__init__("g_arm_trajectory_bridge")

        # Parameters
        self.declare_parameter("rate_hz", 100.0)
        self.rate_hz = float(self.get_parameter("rate_hz").value)
        self.dt = 1.0 / self.rate_hz

        # Expected joints
        self.declare_parameter("joints", ["joint1", "joint2", "joint3", "electromagnet"])
        self.joint_names: List[str] = list(self.get_parameter("joints").value)

        # Publishers per joint
        self.pub_pos: Dict[str, rclpy.publisher.Publisher] = {}
        for j in self.joint_names:
            if j == "electromagnet":
                self.pub_pos[j] = self.create_publisher(Bool, f"/{j}", 10)
            else:
                self.pub_pos[j] = self.create_publisher(Float64, f"/{j}", 10)

        # Last commanded values (initialize to zeros/off)
        self.current_cmd: Dict[str, float] = {j: 0.0 for j in self.joint_names}

        # Action server
        self._as = ActionServer(
            self,
            FollowJointTrajectory,
            "arm_controller/follow_joint_trajectory",
            execute_callback=self.execute_cb,
            goal_callback=self.goal_cb,
            cancel_callback=self.cancel_cb,
        )

        self.get_logger().info(f"Ready: joints={self.joint_names}, rate={self.rate_hz} Hz")

    def goal_cb(self, goal_request: FollowJointTrajectory.Goal):
        # Accept all goals whose joints align with what we expose
        req_names = set(goal_request.trajectory.joint_names)
        have_names = set(self.joint_names)
        if not req_names.issubset(have_names):
            self.get_logger().warn(f"Rejecting goal: unknown joints {req_names - have_names}")
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def cancel_cb(self, goal_handle):
        self.get_logger().info("Cancel requested")
        return CancelResponse.ACCEPT

    def _publish_commands(self, cmd: Dict[str, float]):
        for j, v in cmd.items():
            if j == "electromagnet":
                msg = Bool()
                msg.data = (v >= 0.5)
                self.pub_pos[j].publish(msg)
            else:
                msg = Float64()
                msg.data = float(v)
                self.pub_pos[j].publish(msg)

    def _interp(self, a: float, b: float, t: float) -> float:
        # simple linear interpolation
        return a + (b - a) * t

    async def execute_cb(self, goal_handle):
        self.get_logger().info("Trajectory goal received")
        traj = goal_handle.request.trajectory

        # Build per-point dicts keyed by joint name
        joint_order = traj.joint_names
        points: List[JointTrajectoryPoint] = traj.points

        # Normalize time_from_start into seconds list
        tpoints = [p.time_from_start.sec + p.time_from_start.nanosec * 1e-9 for p in points]
        if not tpoints or tpoints[0] > 1e-6:
            # Ensure we have an initial anchor at t=0
            if points:
                p0 = JointTrajectoryPoint()
                p0.positions = points[0].positions
                p0.time_from_start = type(points[0].time_from_start)()
                points.insert(0, p0)
                tpoints.insert(0, 0.0)

        start_time = self.get_clock().now()
        success = True

        # Iterate intervals between consecutive points
        for i in range(len(points) - 1):
            pA = points[i]
            pB = points[i + 1]
            tA = tpoints[i]
            tB = tpoints[i + 1]
            duration = max(tB - tA, self.dt)

            # Target maps at endpoints
            A = {joint_order[j]: float(pA.positions[j]) for j in range(len(joint_order))}
            B = {joint_order[j]: float(pB.positions[j]) for j in range(len(joint_order))}

            steps = max(1, int(duration / self.dt))
            for k in range(steps):
                if goal_handle.is_cancel_requested:
                    self.get_logger().info("Goal canceled")
                    goal_handle.canceled()
                    # Stop motion (hold last command)
                    self._publish_commands(self.current_cmd)
                    return FollowJointTrajectory.Result(error_code=FollowJointTrajectory.Result.SUCCESSFUL)

                t = (k + 1) / steps
                cmd = {}
                for j in self.joint_names:
                    a = A.get(j, self.current_cmd[j])
                    b = B.get(j, a)
                    cmd[j] = self._interp(a, b, t)

                self._publish_commands(cmd)
                self.current_cmd.update(cmd)

                # Feedback (optional)
                fb = FollowJointTrajectory.Feedback()
                fb.joint_names = self.joint_names
                fb.desired = JointTrajectoryPoint(positions=[cmd[j] for j in self.joint_names])
                goal_handle.publish_feedback(fb)

                await rclpy.task.Future()  # yield to executor
                time.sleep(self.dt)

        # Final point ensured
        self._publish_commands(self.current_cmd)

        goal_handle.succeed()
        result = FollowJointTrajectory.Result()
        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
        self.get_logger().info("Trajectory goal succeeded")
        return result


def main():
    rclpy.init()
    node = TrajectoryBridge()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()
