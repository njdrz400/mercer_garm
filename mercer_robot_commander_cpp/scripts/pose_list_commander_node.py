#!/usr/bin/env python3
"""
Pose list commander node: moves the g-arm through a list of coordinates
(start -> waypoints -> back to start) and publishes status for monitoring.

LED indication uses ROS2 actions only: goals are sent to the pi_gpio_server
(pi_gpio_interface/action/GPIO). There is no direct GPIO access in this node.
"""

import os
import sys
import threading
import time
import yaml

import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from rclpy.action import ActionClient
from geometry_msgs.msg import PoseStamped, Point, Quaternion
from std_msgs.msg import String, Int32, Bool, Float64
from std_srvs.srv import Trigger
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener

# LED control uses the ROS2 action only (no direct GPIO). _set_led_gpio sends goals to
# /pi_gpio_server with action type pi_gpio_interface/action/GPIO.
# Example: ros2 action send_goal /pi_gpio_server pi_gpio_interface/action/GPIO "{gpio: '27,high'}"
try:
    from pi_gpio_interface.action import GPIO
    GPIO_AVAILABLE = True
except ImportError:
    GPIO_AVAILABLE = False
    GPIO = None

# Add scripts dir for go_to_pose_client
script_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, script_dir)
from go_to_pose_client import GoToPoseClient, create_pose_stamped

from g_arm_msgs.action import GoToPose


# State names for publishing
STATE_IDLE = 'idle'
STATE_MOVING = 'moving'
STATE_PAUSING = 'pausing'
STATE_RETURNING = 'returning'
STATE_BACK_AT_START = 'back_at_start'
STATE_CANCELLED = 'cancelled'
STATE_ERROR = 'error'


class PoseListCommanderNode(Node):
    """Runs a sequence: start pose -> waypoints -> back to start; publishes status."""

    def __init__(self):
        super().__init__('pose_list_commander')
        self.declare_parameter('waypoints_file', '')
        self.declare_parameter('frame_id', 'base_link')
        self.declare_parameter('pos_tolerance_m', 0.01)
        self.declare_parameter('ang_tolerance_rad', 0.2)
        self.declare_parameter('timeout_sec',60.0)
        self.declare_parameter('end_effector_frame', 'end_effector_tip')

        self._tf_buffer = Buffer()
        self._tf_listener = TransformListener(self._tf_buffer, self)
        self._base_frame = self.get_parameter('frame_id').get_parameter_value().string_value
        self._ee_frame = self.get_parameter('end_effector_frame').get_parameter_value().string_value

        self._waypoints = []  # list of dicts: {x, y, z, name (optional), electromagnet_on (optional)}
        self._led_color = 'g'  # from config: g, y, or r
        self._load_waypoints()

        self._state = STATE_IDLE
        self._current_index = 0
        self._total_count = 0
        self._current_waypoint_name = ''
        self._cancel_requested = False
        self._run_thread = None
        self._goal_handle = None

        self._client = GoToPoseClient()

        self._state_pub = self.create_publisher(String, 'pose_list_commander/state', 10)
        self._current_index_pub = self.create_publisher(Int32, 'pose_list_commander/current_index', 10)
        self._total_count_pub = self.create_publisher(Int32, 'pose_list_commander/total_count', 10)
        self._back_at_start_pub = self.create_publisher(Bool, 'pose_list_commander/back_at_start', 10)
        self._current_waypoint_name_pub = self.create_publisher(String, 'pose_list_commander/current_waypoint_name', 10)
        self._led_color_pub = self.create_publisher(String, 'pose_list_commander/led_color', 10)
        self._pause_duration_pub = self.create_publisher(Float64, 'pose_list_commander/pause_duration_sec', 10)
        self._waypoints_list_pub = self.create_publisher(String, 'pose_list_commander/waypoints_list', 10)

        self._start_srv = self.create_service(Trigger, 'pose_list_commander/start', self._handle_start)
        self._cancel_srv = self.create_service(Trigger, 'pose_list_commander/cancel', self._handle_cancel)

        # LED control via ROS2 action client: /pi_gpio_server, pi_gpio_interface/action/GPIO (goal.gpio e.g. "17,low")
        self._gpio_action_client = None
        if GPIO_AVAILABLE and GPIO is not None:
            try:
                self._gpio_action_client = ActionClient(self, GPIO, '/pi_gpio_server')
            except Exception as e:
                self.get_logger().warn('GPIO action client failed: %s' % e)
        self._turn_off_leds_at_start()

        self._publish_status(led_color=self._led_color)
        self._publish_waypoints_list()
        self.get_logger().info(
            'Pose list commander ready with %d waypoints. Frame: %s, LED color: %s' % (
                len(self._waypoints), self._base_frame, self._led_color)
        )

    def _turn_off_leds_at_start(self):
        """Send ROS2 action goals to /pi_gpio_server to turn off LEDs (high=off). Red=22, Green=17."""
        if self._gpio_action_client is None:
            return
        if not self._gpio_action_client.wait_for_server(timeout_sec=2.0):
            self.get_logger().info('pi_gpio_server (action server) not available; skipping LED turn-off.')
            return
        for action_spec, label in [('22,high', 'red LED'), ('17,high', 'green LED')]:
            try:
                goal = GPIO.Goal()
                goal.gpio = action_spec
                future = self._gpio_action_client.send_goal_async(goal)
                rclpy.spin_until_future_complete(self, future, timeout_sec=2.0)
                if future.result() is not None and future.result().accepted:
                    self.get_logger().info('Turned off %s (action goal %s)' % (label, action_spec))
                else:
                    self.get_logger().warn('GPIO action goal %s not accepted' % action_spec)
            except Exception as e:
                self.get_logger().warn('GPIO action %s failed: %s' % (action_spec, e))

    def _set_led_gpio(self, led_color):
        """Set LED by sending ROS2 action goals to /pi_gpio_server (pi_gpio_interface/action/GPIO).
        No direct GPIO; goal.gpio format e.g. "27,high" or "17,low". Green=17, Yellow=18, Red=22.
        Fire-and-forget (send_goal_async) for use from sequence thread."""
        if self._gpio_action_client is None:
            return
        if not self._gpio_action_client.wait_for_server(timeout_sec=0.3):
            return
        pin_for_color = {'g': 17, 'y': 18, 'r': 22}
        pin_on = pin_for_color.get(led_color if isinstance(led_color, str) else 'g', 17)
        all_pins = (17, 18, 22)
        try:
            # Turn off all LEDs: send action goals with "pin,high"
            for pin in all_pins:
                goal = GPIO.Goal()
                goal.gpio = '%d,high' % pin
                self._gpio_action_client.send_goal_async(goal)
            # Turn on LED for current color: send action goal with "pin,low"
            goal = GPIO.Goal()
            goal.gpio = '%d,low' % pin_on
            self._gpio_action_client.send_goal_async(goal)
        except Exception as e:
            self.get_logger().warn('LED action (set LED) failed: %s' % e)

    def _publish_waypoints_list(self):
        """Publish waypoint names and coordinates (x, y, z); also log them."""
        lines = []
        for i, wp in enumerate(self._waypoints):
            name = wp.get('name', 'Waypoint %d' % (i + 1))
            x, y, z = wp['x'], wp['y'], wp['z']
            lines.append('%d. %s   (%.3f, %.3f, %.3f)' % (i + 1, name, x, y, z))
        msg = '\n'.join(lines) if lines else ''
        self._waypoints_list_pub.publish(String(data=msg))
        if msg:
            self.get_logger().info('Waypoint coordinates:\n%s' % msg)

    def _normalize_led(self, raw, default='g'):
        """Normalize led color to g, y, or r. Accepts g/y/r or green/yellow/red."""
        if not isinstance(raw, str):
            return default
        c = raw.strip().lower()
        if c in ('g', 'green'):
            return 'g'
        if c in ('y', 'yellow'):
            return 'y'
        if c in ('r', 'red'):
            return 'r'
        return default

    def _load_waypoints(self):
        """
        Load YAML with:
          waypoints: map of name -> { x, y, z } (coordinates only)
          path: list of steps in order. Each step is a dict with wp (name) and optional
                led (g/y/r), em_on, pause_sec.
        """
        waypoints_file = self.get_parameter('waypoints_file').get_parameter_value().string_value
        if not waypoints_file:
            self.get_logger().info('No waypoints_file parameter. Set it to a YAML with waypoints and path.')
            return
        path_str = waypoints_file if os.path.isabs(waypoints_file) else os.path.join(script_dir, waypoints_file)
        if not os.path.isfile(path_str):
            self.get_logger().warn('Waypoints file not found: %s' % path_str)
            return
        try:
            with open(path_str, 'r') as f:
                data = yaml.safe_load(f)
            if data is None:
                data = {}
            if not isinstance(data, dict):
                self.get_logger().warn('YAML root must be a dict with waypoints and path.')
                return
            raw = data.get('led_color', 'g')
            if isinstance(raw, str):
                self._led_color = self._normalize_led(raw, 'g')
            # waypoints: name -> { x, y, z }
            wp_defs = data.get('waypoints')
            if not isinstance(wp_defs, dict):
                self.get_logger().warn('YAML must have "waypoints" as a map of name -> { x, y, z }.')
                return
            path_list = data.get('path')
            if not isinstance(path_list, list):
                self.get_logger().warn('YAML must have "path" as a list of steps (waypoint name + optional led_color, electromagnet_on, pause_sec).')
                return
            for idx, step in enumerate(path_list):
                if isinstance(step, str):
                    step = {'wp': step}
                if not isinstance(step, dict):
                    continue
                name = step.get('wp') or step.get('waypoint')
                if name is None:
                    continue
                name = str(name).strip()
                if not name:
                    continue
                coords = wp_defs.get(name)
                if not isinstance(coords, dict) or 'x' not in coords or 'y' not in coords or 'z' not in coords:
                    self.get_logger().warn('Path step %d: waypoint "%s" not found or missing x,y,z in waypoints.' % (idx + 1, name))
                    continue
                wp_led_raw = step.get('led') or step.get('led_color')
                wp_led = self._normalize_led(wp_led_raw, self._led_color) if isinstance(wp_led_raw, str) else self._led_color
                pause_sec = 0.0
                if 'pause_sec' in step:
                    try:
                        pause_sec = float(step['pause_sec'])
                        if pause_sec < 0.0:
                            pause_sec = 0.0
                    except (TypeError, ValueError):
                        pass
                em_on = step.get('em_on')
                if em_on is None:
                    em_on = step.get('electromagnet_on', False)
                self._waypoints.append({
                    'x': float(coords['x']), 'y': float(coords['y']), 'z': float(coords['z']),
                    'name': name,
                    'electromagnet_on': bool(em_on),
                    'led_color': wp_led,
                    'pause_sec': pause_sec
                })
            if not self._waypoints:
                self.get_logger().info('No path steps resolved. Check waypoints names and path entries.')
        except Exception as e:
            self.get_logger().warn('Could not load waypoints from %s: %s' % (path_str, e))

    def _get_current_pose_stamped(self):
        """Get current end effector pose in base_frame."""
        try:
            t = self._tf_buffer.lookup_transform(
                self._base_frame,
                self._ee_frame,
                rclpy.time.Time(),
                timeout=rclpy.duration.Duration(seconds=2.0)
            )
            pose = PoseStamped()
            pose.header = t.header
            pose.pose.position.x = t.transform.translation.x
            pose.pose.position.y = t.transform.translation.y
            pose.pose.position.z = t.transform.translation.z
            pose.pose.orientation = t.transform.rotation
            return pose
        except TransformException as e:
            self.get_logger().error('TF lookup failed: %s' % e)
            return None

    def _publish_status(self, state=None, current_index=None, total_count=None, back_at_start=None,
                        current_waypoint_name=None, led_color=None):
        if state is not None:
            self._state = state
        if current_index is not None:
            self._current_index = current_index
        if total_count is not None:
            self._total_count = total_count
        if current_waypoint_name is not None:
            self._current_waypoint_name = current_waypoint_name
        if led_color is not None:
            self._led_color = led_color

        self._state_pub.publish(String(data=self._state))
        self._current_index_pub.publish(Int32(data=self._current_index))
        self._total_count_pub.publish(Int32(data=self._total_count))
        self._current_waypoint_name_pub.publish(String(data=self._current_waypoint_name))
        self._led_color_pub.publish(String(data=self._led_color))
        if back_at_start is not None:
            self._back_at_start_pub.publish(Bool(data=back_at_start))
        # Update physical LEDs via ROS2 action goals (low=on): green=17, yellow=18, red=22
        self._set_led_gpio(self._led_color)

    def _handle_start(self, request, response):
        del request
        if self._state not in (STATE_IDLE, STATE_BACK_AT_START, STATE_CANCELLED, STATE_ERROR):
            response.success = False
            response.message = 'Sequence already running'
            return response
        if not self._waypoints:
            response.success = False
            response.message = 'No waypoints loaded'
            return response
        if not self._client.wait_for_server(timeout_sec=2.0):
            response.success = False
            response.message = 'GoToPose action server not available'
            return response
        start_pose = self._get_current_pose_stamped()
        if start_pose is None:
            response.success = False
            response.message = 'Could not get current pose (TF)'
            return response
        self._cancel_requested = False
        self._run_thread = threading.Thread(
            target=self._run_sequence,
            args=(start_pose,),
            daemon=True
        )
        self._run_thread.start()
        response.success = True
        response.message = 'Sequence started'
        return response

    def _handle_cancel(self, request, response):
        del request
        self._cancel_requested = True
        if self._goal_handle is not None:
            try:
                cancel_future = self._goal_handle.cancel_goal_async()
                rclpy.spin_until_future_complete(self, cancel_future, timeout_sec=1.0)
            except Exception:
                pass
        response.success = True
        response.message = 'Cancel requested'
        return response

    def _run_sequence(self, start_pose):
        pos_tol = self.get_parameter('pos_tolerance_m').get_parameter_value().double_value
        ang_tol = self.get_parameter('ang_tolerance_rad').get_parameter_value().double_value
        timeout = self.get_parameter('timeout_sec').get_parameter_value().double_value

        # Full sequence: start (already there) -> waypoint_1 .. waypoint_N -> start
        total = len(self._waypoints) + 1  # +1 for "back to start"
        # Start: use top-level default led_color
        self._publish_status(state=STATE_MOVING, current_index=0, total_count=total, back_at_start=False,
                             current_waypoint_name='Start', led_color=self._led_color)

        for i, wp in enumerate(self._waypoints):
            if self._cancel_requested:
                self._publish_status(state=STATE_CANCELLED, current_index=i, total_count=total, back_at_start=False,
                                     current_waypoint_name=wp.get('name', 'Waypoint %d' % (i + 1)),
                                     led_color=wp.get('led_color', self._led_color))
                return
            target = create_pose_stamped(
                self._base_frame,
                wp['x'], wp['y'], wp['z']
            )
            wp_name = wp.get('name', 'Waypoint %d' % (i + 1))
            wp_led = wp.get('led_color', self._led_color)
            self._publish_status(state=STATE_MOVING, current_index=i, total_count=total, back_at_start=False,
                                current_waypoint_name=wp_name, led_color=wp_led)
            self.get_logger().info('Moving to waypoint %s (%d/%d) (%.3f, %.3f, %.3f)' % (
                wp_name, i + 1, len(self._waypoints), wp['x'], wp['y'], wp['z']))

            accepted = self._client.send_goal(
                target,
                pos_tolerance_m=pos_tol,
                ang_tolerance_rad=ang_tol,
                timeout_sec=timeout,
                allow_orientation=True,
                electromagnet_on=wp.get('electromagnet_on', False)
            )
            if not accepted:
                self._publish_status(state=STATE_ERROR, current_index=i, total_count=total, back_at_start=False,
                                    current_waypoint_name=wp_name, led_color='r')
                return
            self._goal_handle = self._client._goal_handle
            try:
                result = self._client.wait_for_result(timeout_sec=timeout + 5.0)
            except Exception as e:
                self._goal_handle = None
                self.get_logger().error('Action failed (e.g. pose not calculable): %s' % e)
                self._publish_status(state=STATE_ERROR, current_index=i, total_count=total, back_at_start=False,
                                    current_waypoint_name=wp_name, led_color='r')
                return
            self._goal_handle = None
            if not result or not result.success:
                self._publish_status(state=STATE_ERROR, current_index=i, total_count=total, back_at_start=False,
                                    current_waypoint_name=wp_name, led_color='r')
                return
            # Pause between waypoints if configured (cancel can interrupt)
            pause_sec = wp.get('pause_sec', 0.0)
            if pause_sec > 0.0 and not self._cancel_requested:
                self._pause_duration_pub.publish(Float64(data=float(pause_sec)))
                self._publish_status(state=STATE_PAUSING, current_index=i + 1, total_count=total, back_at_start=False,
                                    current_waypoint_name=wp_name, led_color=wp_led)
                self.get_logger().info('Pausing %.2f s after waypoint %s' % (pause_sec, wp_name))
                elapsed = 0.0
                chunk = 0.2
                while elapsed < pause_sec and not self._cancel_requested:
                    time.sleep(min(chunk, pause_sec - elapsed))
                    elapsed += chunk
                if self._cancel_requested:
                    self._publish_status(state=STATE_CANCELLED, current_index=i + 1, total_count=total,
                                        back_at_start=False, current_waypoint_name=wp_name, led_color=wp_led)
                    return
        # Return to start (use default led_color)
        if self._cancel_requested:
            self._publish_status(state=STATE_CANCELLED, current_index=len(self._waypoints), total_count=total,
                                back_at_start=False, current_waypoint_name='Return to start',
                                led_color=self._led_color)
            return
        self._publish_status(state=STATE_RETURNING, current_index=len(self._waypoints), total_count=total,
                            back_at_start=False, current_waypoint_name='Return to start',
                            led_color=self._led_color)
        self.get_logger().info('Returning to start pose')
        accepted = self._client.send_goal(
            start_pose,
            pos_tolerance_m=pos_tol,
            ang_tolerance_rad=ang_tol,
            timeout_sec=timeout,
            allow_orientation=True,
            electromagnet_on=False
        )
        if not accepted:
            self._publish_status(state=STATE_ERROR, current_index=total - 1, total_count=total, back_at_start=False,
                                current_waypoint_name='Return to start', led_color='r')
            return
        self._goal_handle = self._client._goal_handle
        try:
            result = self._client.wait_for_result(timeout_sec=timeout + 5.0)
        except Exception as e:
            self._goal_handle = None
            self.get_logger().error('Action failed on return to start (e.g. pose not calculable): %s' % e)
            self._publish_status(state=STATE_ERROR, current_index=total - 1, total_count=total, back_at_start=False,
                                current_waypoint_name='Return to start', led_color='r')
            return
        self._goal_handle = None
        if self._cancel_requested:
            self._publish_status(state=STATE_CANCELLED, current_index=total - 1, total_count=total, back_at_start=False,
                                current_waypoint_name='Return to start', led_color=self._led_color)
            return
        if not result or not result.success:
            self._publish_status(state=STATE_ERROR, current_index=total - 1, total_count=total, back_at_start=False,
                                current_waypoint_name='Return to start', led_color='r')
            return
        self._publish_status(state=STATE_BACK_AT_START, current_index=total, total_count=total, back_at_start=True,
                            current_waypoint_name='Start', led_color=self._led_color)
        self.get_logger().info('Back at start pose.')
        self._back_at_start_pub.publish(Bool(data=True))


def main():
    rclpy.init()
    node = PoseListCommanderNode()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
