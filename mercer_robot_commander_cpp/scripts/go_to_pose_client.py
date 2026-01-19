#!/usr/bin/env python3
"""
Python client for GoToPose action server
Controls the robot arm and electromagnet
"""

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped, Point, Quaternion
from g_arm_msgs.action import GoToPose
import sys
import argparse


class GoToPoseClient(Node):
    def __init__(self):
        super().__init__('go_to_pose_client')
        self._action_client = ActionClient(self, GoToPose, 'go_to_pose')
        self._goal_handle = None
        self._result_future = None

    def wait_for_server(self, timeout_sec=10.0):
        """Wait for the action server to become available"""
        self.get_logger().info('Waiting for action server...')
        if not self._action_client.wait_for_server(timeout_sec=timeout_sec):
            self.get_logger().error('Action server not available after {} seconds'.format(timeout_sec))
            return False
        self.get_logger().info('Action server available')
        return True

    def send_goal(self, target_pose, pos_tolerance_m=0.01, ang_tolerance_rad=0.2,
                  timeout_sec=5.0, allow_orientation=False, electromagnet_on=False,
                  planner_frame='', speed_scale=0.0, max_joint_vel=0.0, max_joint_acc=0.0):
        """
        Send a goal to the GoToPose action server
        
        Args:
            target_pose: PoseStamped with target position and orientation
            pos_tolerance_m: Position tolerance in meters
            ang_tolerance_rad: Orientation tolerance in radians
            timeout_sec: Maximum time to complete the goal
            allow_orientation: If True, ignore orientation constraints
            electromagnet_on: If True, turn electromagnet ON; if False, turn OFF
            planner_frame: Optional planner frame (empty string uses default)
            speed_scale: Speed scaling factor (0.0 = use default)
            max_joint_vel: Maximum joint velocity (0.0 = use default)
            max_joint_acc: Maximum joint acceleration (0.0 = use default)
        
        Returns:
            True if goal was accepted, False otherwise
        """
        goal_msg = GoToPose.Goal()
        goal_msg.target = target_pose
        goal_msg.pos_tolerance_m = pos_tolerance_m
        goal_msg.ang_tolerance_rad = ang_tolerance_rad
        goal_msg.timeout_sec = timeout_sec
        goal_msg.allow_orientation = allow_orientation
        goal_msg.electromagnet_on = electromagnet_on
        goal_msg.planner_frame = planner_frame
        goal_msg.speed_scale = speed_scale
        goal_msg.max_joint_vel = max_joint_vel
        goal_msg.max_joint_acc = max_joint_acc

        self.get_logger().info('Sending goal...')
        self.get_logger().info('  Position: x={:.3f}, y={:.3f}, z={:.3f}'.format(
            target_pose.pose.position.x,
            target_pose.pose.position.y,
            target_pose.pose.position.z))
        self.get_logger().info('  Orientation: w={:.3f}, x={:.3f}, y={:.3f}, z={:.3f}'.format(
            target_pose.pose.orientation.w,
            target_pose.pose.orientation.x,
            target_pose.pose.orientation.y,
            target_pose.pose.orientation.z))
        self.get_logger().info('  Electromagnet: {}'.format('ON' if electromagnet_on else 'OFF'))
        self.get_logger().info('  Allow orientation: {}'.format(allow_orientation))

        send_goal_future = self._action_client.send_goal_async(
            goal_msg,
            feedback_callback=self.feedback_callback
        )

        rclpy.spin_until_future_complete(self, send_goal_future)
        self._goal_handle = send_goal_future.result()

        if not self._goal_handle.accepted:
            self.get_logger().error('Goal rejected')
            return False

        self.get_logger().info('Goal accepted')
        self._result_future = self._goal_handle.get_result_async()
        return True

    def feedback_callback(self, feedback_msg):
        """Callback for action feedback"""
        feedback = feedback_msg.feedback
        self.get_logger().info(
            'Feedback: state={}, pos_error={:.4f}m, ang_error={:.4f}rad, progress={:.1f}% - {}'.format(
                feedback.state,
                feedback.pos_error_m,
                feedback.ang_error_rad,
                feedback.progress * 100.0,
                feedback.detail
            )
        )

    def wait_for_result(self, timeout_sec=None):
        """
        Wait for the action result
        
        Args:
            timeout_sec: Timeout in seconds (None = wait indefinitely)
        
        Returns:
            GoToPose.Result if successful, None otherwise
        """
        if self._result_future is None:
            self.get_logger().error('No goal sent or goal was rejected')
            return None

        self.get_logger().info('Waiting for result...')
        if timeout_sec is not None:
            rclpy.spin_until_future_complete(self, self._result_future, timeout_sec=timeout_sec)
        else:
            rclpy.spin_until_future_complete(self, self._result_future)

        result = self._result_future.result().result

        if result.success:
            self.get_logger().info('Goal succeeded!')
            self.get_logger().info('  Final position error: {:.6f} m'.format(result.final_pos_error_m))
            self.get_logger().info('  Final orientation error: {:.6f} rad'.format(result.final_ang_error_rad))
            self.get_logger().info('  Final joint positions: {}'.format(result.final_joint_positions))
        else:
            self.get_logger().error('Goal failed!')
            self.get_logger().error('  Error code: {}'.format(result.error_code))
            self.get_logger().error('  Message: {}'.format(result.message))
            self.get_logger().error('  Final position error: {:.6f} m'.format(result.final_pos_error_m))
            self.get_logger().error('  Final orientation error: {:.6f} rad'.format(result.final_ang_error_rad))

        return result

    def cancel_goal(self):
        """Cancel the current goal"""
        if self._goal_handle is not None:
            self.get_logger().info('Canceling goal...')
            cancel_future = self._goal_handle.cancel_goal_async()
            rclpy.spin_until_future_complete(self, cancel_future)
            self.get_logger().info('Goal canceled')


def create_pose_stamped(frame_id, x, y, z, qx=0.0, qy=0.0, qz=0.0, qw=1.0):
    """Helper function to create a PoseStamped message"""
    pose = PoseStamped()
    pose.header.frame_id = frame_id
    pose.header.stamp = rclpy.time.Time().to_msg()
    pose.pose.position = Point(x=x, y=y, z=z)
    pose.pose.orientation = Quaternion(x=qx, y=qy, z=qz, w=qw)
    return pose


def main():
    parser = argparse.ArgumentParser(description='GoToPose action client')
    parser.add_argument('--x', type=float, default=0.25, help='Target X position (meters)')
    parser.add_argument('--y', type=float, default=0.0, help='Target Y position (meters)')
    parser.add_argument('--z', type=float, default=0.20, help='Target Z position (meters)')
    parser.add_argument('--qx', type=float, default=0.0, help='Quaternion X component')
    parser.add_argument('--qy', type=float, default=0.0, help='Quaternion Y component')
    parser.add_argument('--qz', type=float, default=0.0, help='Quaternion Z component')
    parser.add_argument('--qw', type=float, default=1.0, help='Quaternion W component')
    parser.add_argument('--frame', type=str, default='base_link', help='Target frame ID')
    parser.add_argument('--pos-tol', type=float, default=0.01, help='Position tolerance (meters)')
    parser.add_argument('--ang-tol', type=float, default=0.2, help='Orientation tolerance (radians)')
    parser.add_argument('--timeout', type=float, default=10.0, help='Timeout (seconds)')
    parser.add_argument('--allow-orientation', action='store_true', 
                       help='Ignore orientation constraints')
    parser.add_argument('--electromagnet-on', action='store_true',
                       help='Turn electromagnet ON after reaching pose')
    parser.add_argument('--electromagnet-off', action='store_true',
                       help='Turn electromagnet OFF after reaching pose')
    parser.add_argument('--speed-scale', type=float, default=0.0,
                       help='Speed scaling factor (0.0 = use default, 0.0-1.0)')
    parser.add_argument('--cancel', action='store_true', help='Cancel current goal')

    args = parser.parse_args()

    rclpy.init()

    client = GoToPoseClient()

    if not client.wait_for_server(timeout_sec=10.0):
        client.get_logger().error('Failed to connect to action server')
        return 1

    if args.cancel:
        client.cancel_goal()
        return 0

    # Determine electromagnet state
    electromagnet_on = False
    if args.electromagnet_on:
        electromagnet_on = True
    elif args.electromagnet_off:
        electromagnet_on = False
    # If neither specified, default to False (OFF)

    # Create target pose
    target_pose = create_pose_stamped(
        args.frame,
        args.x, args.y, args.z,
        args.qx, args.qy, args.qz, args.qw
    )

    # Send goal
    if not client.send_goal(
        target_pose,
        pos_tolerance_m=args.pos_tol,
        ang_tolerance_rad=args.ang_tol,
        timeout_sec=args.timeout,
        allow_orientation=args.allow_orientation,
        electromagnet_on=electromagnet_on,
        speed_scale=args.speed_scale
    ):
        return 1

    # Wait for result
    result = client.wait_for_result(timeout_sec=args.timeout + 5.0)

    if result is None:
        client.get_logger().error('Failed to get result')
        return 1

    return 0 if result.success else 1


if __name__ == '__main__':
    sys.exit(main())
