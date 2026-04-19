#!/usr/bin/env python3
"""
ROS2 node: Tk interface to play tic-tac-toe with the macropad.
Game modes: 1 Player vs Computer, 2 Player, Computer vs Computer.
"""

import os
import queue
import random
import time
import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext, filedialog

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from tf2_ros import Buffer, TransformListener, TransformException
from geometry_msgs.msg import PoseStamped, Point, Quaternion
from g_arm_msgs.action import GoToPose
from ament_index_python.packages import get_package_share_directory
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration as RosDuration
from action_msgs.msg import GoalStatus

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    serial = None

try:
    import yaml
except ImportError:
    yaml = None

# Macropad sends kp03..kp11 for grid keys (key index 3–11 → cell 0–8)
KEY_TO_CELL = {f"kp{i:02d}": i - 3 for i in range(3, 12)}
KEY_TO_CELL.update({f"key_pressed_{i}": i - 3 for i in range(3, 12)})

WIN_LINES = [
    (0, 1, 2), (3, 4, 5), (6, 7, 8),
    (0, 3, 6), (1, 4, 7), (2, 5, 8),
    (0, 4, 8), (2, 4, 6),
]


def check_winner(board):
    """Return 'X', 'O', 'Tie', or None."""
    for a, b, c in WIN_LINES:
        if board[a] and board[a] == board[b] == board[c]:
            return board[a]
    if all(board[i] for i in range(9)):
        return 'Tie'
    return None


def empty_cells(board):
    return [i for i in range(9) if board[i] is None]


def minimax(board, player, depth=0):
    """Score for current board: +10 if O wins, -10 if X wins, 0 tie. O is maximizing."""
    winner = check_winner(board)
    if winner == 'O':
        return 10 - depth
    if winner == 'X':
        return depth - 10
    if winner == 'Tie':
        return 0
    empty = empty_cells(board)
    if not empty:
        return 0
    opponent = 'X' if player == 'O' else 'O'
    if player == 'O':
        best = -999
        for cell in empty:
            board[cell] = 'O'
            score = minimax(board, 'X', depth + 1)
            board[cell] = None
            best = max(best, score)
        return best
    else:
        best = 999
        for cell in empty:
            board[cell] = 'X'
            score = minimax(board, 'O', depth + 1)
            board[cell] = None
            best = min(best, score)
        return best


def best_move(board, side):
    """Return best cell for side ('X' or 'O') using minimax."""
    empty = empty_cells(board)
    if not empty:
        return None
    if side == 'O':
        best_score = -999
        best_cell = empty[0]
        for cell in empty:
            board[cell] = 'O'
            score = minimax(board, 'X')
            board[cell] = None
            if score > best_score:
                best_score = score
                best_cell = cell
        return best_cell
    else:
        best_score = 999
        best_cell = empty[0]
        for cell in empty:
            board[cell] = 'X'
            score = minimax(board, 'O')
            board[cell] = None
            if score < best_score:
                best_score = score
                best_cell = cell
        return best_cell


def list_serial_ports():
    if serial is None:
        return []
    ports = serial.tools.list_ports.comports()
    return [(p.device, f"{p.device} — {p.description}") for p in ports]


class MacropadTictactoeNode(Node):
    """ROS2 node with Tk window: status, game mode selection, reset; interacts with macropad over serial."""

    GAME_MODES = [
        "1 Player vs Computer",
        "2 Player",
        "Computer vs Computer",
    ]

    # Pick/place: pick hover → pickup z → magnet ON → pick hover → transit → drop hover → drop → magnet OFF → MID → magnet OFF
    _ROBOT_PLACE_NUM_STEPS = 10

    def __init__(self):
        super().__init__('macropad_tictactoe_node')
        self._ser = None
        self._read_queue = queue.Queue()
        self._read_buffer = ""
        self._reading = False
        self._after_id = None
        self._last_heartbeat_time = None  # macropad sends hb99 ~every second when alive

        self._board = [None] * 9
        self._turn = 'X'  # X = red (rtrn/sr), O = blue (btrn/sb)
        self._game_over = False
        self._winner = None  # 'X', 'O', 'Tie', or None
        self._game_mode_idx = 0  # 0=1P, 1=2P, 2=CvC
        self._pending_computer_move_id = None

        # Waypoints for robot arm (name -> {x, y, z}); loaded from config/waypoints.yaml
        self._waypoints = {}
        self._load_waypoints()

        # Where each tic-tac-toe piece is (waypoint name). At game start: red at R00-R04, blue at B00-B04.
        # Board cells 0-8 use waypoints T00-T08. Updated when placing a piece.
        self._red_piece_locations = ["R00", "R01", "R02", "R03", "R04"]
        self._blue_piece_locations = ["B00", "B01", "B02", "B03", "B04"]

        # Robot arm: move piece from red/blue home to board cell (GoToPose action)
        self._go_to_pose_client = ActionClient(self, GoToPose, 'go_to_pose')
        # TF: used for calibration "save from current pose"
        self._base_frame = 'base_link'
        self._end_effector_frame = 'end_effector_tip'  # must exist in TF tree
        self._tf_buffer = Buffer()
        self._tf_listener = TransformListener(self._tf_buffer, self)
        self._robot_move_pick = None   # waypoint name (R0x or B0x) while move in progress
        self._robot_move_place = None  # waypoint name (T0x)
        self._robot_move_step = 0      # see _robot_place_piece_step (0.._ROBOT_PLACE_NUM_STEPS-1)
        # Extra guards (beyond step-by-step chaining):
        # - sequence_busy: a multi-step place sequence is active
        # - pose_goal_in_flight: a GoToPose goal is currently executing
        # - em_goal_in_flight: an electromagnet FollowJointTrajectory goal is executing
        self._robot_sequence_busy = False
        self._pose_goal_in_flight = False
        self._em_goal_in_flight = False
        # When 2P mode is active, we delay enabling the next player's input until
        # the robot finishes all pose changes for the current move.
        self._pending_turn_value = None   # 'X' or 'O'
        self._pending_turn_command = None # 'rtrn' or 'btrn'

        # Electromagnet control (separate from GoToPose) to guarantee ON/OFF
        # GoToPose server toggles electromagnet only after successful motion and may skip
        # OFF if it cannot read jointPWM correctly from /joint_states.
        self._em_tool_action_client = ActionClient(
            self, FollowJointTrajectory, '/tool_controller/follow_joint_trajectory'
        )
        self._em_magnet_action_client = ActionClient(
            self, FollowJointTrajectory, '/magnet_controller/follow_joint_trajectory'
        )
        # Track last manual electromagnet state for toggle button (False = OFF)
        self._manual_em_last_state = False
        # When reset is pressed: queue of (from_waypoint, to_waypoint) to return pieces to home
        self._reset_return_queue = None

        self._root = None
        self._status_var = None
        self._port_combo = None
        self._connect_btn = None
        self._mode_combo = None
        self._reset_btn = None
        self._log_text = None

    def _load_waypoints(self):
        """Load waypoints from the active waypoints YAML path."""
        if yaml is None:
            self.get_logger().warn("python3-yaml not available; waypoints not loaded")
            return
        path = self._waypoints_yaml_path()
        try:
            if os.path.isfile(path):
                with open(path, 'r') as f:
                    data = yaml.safe_load(f)
                self._waypoints = data.get('waypoints', {})
                self.get_logger().info(
                    "Loaded %d waypoints from %s" % (len(self._waypoints), path)
                )
            else:
                self.get_logger().warn("waypoints.yaml not found at %s" % path)
                self._waypoints = {}
        except Exception as e:
            self.get_logger().warn("Could not load waypoints: %s" % e)
            self._waypoints = {}

    def _on_reload_waypoints(self):
        """Reload waypoints from YAML on demand."""
        self._load_waypoints()
        if getattr(self, '_log_text', None) is not None:
            self._log("Waypoints reloaded from %s (%d waypoints)." % (self._waypoints_yaml_path(), len(self._waypoints)))
            self._log_waypoints()

    def _on_browse_waypoints_yaml(self):
        """Open a dialog to select a waypoints.yaml file, then reload it."""
        initial = ''
        try:
            initial = self._waypoints_yaml_path_var.get().strip()
        except Exception:
            initial = ''

        selected = filedialog.askopenfilename(
            title="Select waypoints.yaml",
            initialdir=os.path.dirname(initial) if initial else None,
            filetypes=[("YAML files", "*.yaml *.yml"), ("All files", "*.*")]
        )
        if not selected:
            return
        self._waypoints_yaml_path_var.set(selected)
        self._on_reload_waypoints()

    def _default_waypoints_yaml_path(self):
        """Return default absolute path to macropad_tictactoe/config/waypoints.yaml."""
        
        return '/home/rosuser/mercer_garm/ros2/src/macropad_tictactoe/config/waypoints.yaml'

    def _waypoints_yaml_path(self):
        """Return active absolute path to waypoints.yaml (GUI override if provided)."""
        override = None
        if getattr(self, '_waypoints_yaml_path_var', None) is not None:
            try:
                override = self._waypoints_yaml_path_var.get().strip()
            except Exception:
                override = None

        if override:
            expanded = os.path.expanduser(override)
            abs_path = expanded if os.path.isabs(expanded) else os.path.abspath(expanded)
            return abs_path

        return self._default_waypoints_yaml_path()

    def _persist_waypoints(self):
        """Write the current self._waypoints back to config/waypoints.yaml."""
        if yaml is None:
            raise RuntimeError("python3-yaml not available; cannot save waypoints")
        path = self._waypoints_yaml_path()
        out_dir = os.path.dirname(path) or "."
        if not os.path.isdir(out_dir):
            raise RuntimeError("Directory for waypoints.yaml does not exist: %s" % out_dir)

        # Keep the same top-level structure the loader expects.
        data = {'waypoints': dict(self._waypoints)}
        if os.path.isfile(path):
            try:
                with open(path, 'r') as f:
                    loaded = yaml.safe_load(f) or {}
                if isinstance(loaded, dict) and 'waypoints' in loaded:
                    data = loaded
                    data['waypoints'] = dict(self._waypoints)
            except Exception:
                # If reading fails, still try to write the minimal structure.
                pass

        tmp_path = path + ".tmp"
        with open(tmp_path, 'w') as f:
            yaml.safe_dump(data, f, sort_keys=False)
        os.replace(tmp_path, path)

    def _update_waypoint_xyz(self, waypoint_name, x_m, y_m, z_m):
        """Update x/y/z for a waypoint in-memory (does not write YAML)."""
        self._waypoints[waypoint_name] = {'x': float(x_m), 'y': float(y_m), 'z': float(z_m)}

    def _get_current_pose_from_tf(self, warn_on_fail=True):
        """Get current end-effector pose from TF (returns PoseStamped or None)."""
        try:
            transform = self._tf_buffer.lookup_transform(
                self._base_frame,
                self._end_effector_frame,
                rclpy.time.Time(),
            )
            pose = PoseStamped()
            pose.header.frame_id = self._base_frame
            pose.header.stamp = transform.header.stamp
            pose.pose.position = Point(
                x=transform.transform.translation.x,
                y=transform.transform.translation.y,
                z=transform.transform.translation.z,
            )
            pose.pose.orientation = transform.transform.rotation
            return pose
        except TransformException as ex:
            if warn_on_fail:
                self.get_logger().warn("Calibration: could not read current pose from TF: %s" % ex)
            return None

    def _get_piece_heights_m(self):
        """Return (hover_m, pickup_m, transit_m, drop_m) as offsets added to waypoint z (meters)."""
        try:
            hover_mm = float(self._hover_height_mm_var.get().strip())
        except (ValueError, AttributeError):
            hover_mm = 60.0
        try:
            pickup_mm = float(self._pickup_height_mm_var.get().strip())
        except (ValueError, AttributeError):
            pickup_mm = 0.0
        try:
            transit_mm = float(self._transit_height_mm_var.get().strip())
        except (ValueError, AttributeError):
            transit_mm = 60.0
        try:
            drop_mm = float(self._drop_height_mm_var.get().strip())
        except (ValueError, AttributeError):
            drop_mm = 20.0
        return (
            hover_mm / 1000.0,
            pickup_mm / 1000.0,
            transit_mm / 1000.0,
            drop_mm / 1000.0,
        )

    def _waypoint_pose(self, waypoint_name, frame_id='base_link'):
        """Build PoseStamped for a waypoint name (must be in self._waypoints)."""
        pt = self._waypoints.get(waypoint_name)
        if not pt:
            return None
        pose = PoseStamped()
        pose.header.frame_id = frame_id
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.pose.position = Point(
            x=float(pt.get('x', 0)),
            y=float(pt.get('y', 0)),
            z=float(pt.get('z', 0)))
        pose.pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
        return pose

    def _robot_is_busy(self):
        return bool(self._robot_sequence_busy or self._pose_goal_in_flight or self._em_goal_in_flight)

    def _robot_send_em_command_async(self, turn_on, step_for_logging):
        """Send a direct electromagnet ON/OFF command and advance place sequence.

        Uses FollowJointTrajectory on the electromagnet controller directly so we do not
        rely on GoToPose server's internal "current_pwm" check.
        """
        if self._em_goal_in_flight:
            return
        self._em_goal_in_flight = True
        target_pwm = 1.0 if turn_on else 0.0

        client = None
        controller_name = None
        for name, c in (
            ("tool_controller", self._em_tool_action_client),
            ("magnet_controller", self._em_magnet_action_client),
        ):
            if c.wait_for_server(timeout_sec=0.2):
                client = c
                controller_name = name
                break

        if client is None:
            self.get_logger().warn("Electromagnet action server not available; skipping em command")
            self._log("Robot magnet command skipped (server not available).")
            self._em_goal_in_flight = False
            # Still advance sequence to avoid deadlock
            self._robot_move_step += 1
            self._log(
                "Robot magnet step %d/%d completed (skipped)."
                % (self._robot_move_step, self._ROBOT_PLACE_NUM_STEPS)
            )
            if self._robot_move_step >= self._ROBOT_PLACE_NUM_STEPS:
                from_wp = self._robot_move_pick
                to_wp = self._robot_move_place
                self._robot_move_pick = self._robot_move_place = None
                self._robot_move_step = 0
                self._robot_sequence_busy = False
                self._manual_em_last_state = False
                self._schedule_update_magnet_button()
                if self._reset_return_queue is not None:
                    for i in range(5):
                        if self._red_piece_locations[i] == from_wp:
                            self._red_piece_locations[i] = to_wp
                            break
                        if self._blue_piece_locations[i] == from_wp:
                            self._blue_piece_locations[i] = to_wp
                            break
                    self._update_piece_locations_display()
                    if self._reset_return_queue:
                        from_next, to_next = self._reset_return_queue.pop(0)
                        self._robot_move_pick = from_next
                        self._robot_move_place = to_next
                        self._robot_move_step = 0
                        self._robot_sequence_busy = True
                        self._log("Robot: reset - returning %s -> %s" % (from_next, to_next))
                        if self._root and self._root.winfo_exists():
                            self._root.after(250, self._robot_place_piece_step)
                        else:
                            self._robot_place_piece_step()
                    else:
                        self._reset_return_queue = None
                        self._log("Reset: all pieces returned (magnet skipped). Resetting game.")
                        self._do_logical_reset()
                else:
                    self.get_logger().info("Robot placed piece; at MID, waiting for next command.")
                    self._log("Robot: piece placed, at MID (magnet off), waiting for next command.")
                self._set_robot_pose_status("(at MID, magnet off)", "Done: at MID, waiting for next command.")
                return
            if self._root and self._root.winfo_exists():
                self._root.after(250, self._robot_place_piece_step)
            else:
                self._robot_place_piece_step()
            return

        goal_msg = FollowJointTrajectory.Goal()
        goal_msg.trajectory = JointTrajectory()
        goal_msg.trajectory.joint_names = ["jointPWM"]
        point = JointTrajectoryPoint()
        point.positions = [target_pwm]
        point.time_from_start = RosDuration(sec=0, nanosec=500_000_000)  # 0.5s
        goal_msg.trajectory.points = [point]

        self._log(
            "Robot magnet command (step %d/%d): %s via %s (jointPWM=%.1f)"
            % (
                step_for_logging + 1,
                self._ROBOT_PLACE_NUM_STEPS,
                "ON" if turn_on else "OFF",
                controller_name,
                target_pwm,
            )
        )
        self._set_robot_pose_status(
            "(electromagnet %s)" % ("ON" if turn_on else "OFF"),
            "Electromagnet command..."
        )

        send_future = client.send_goal_async(goal_msg)
        send_future.add_done_callback(lambda f: self._robot_em_goal_response_callback(f, turn_on, step_for_logging))

    def _send_manual_em_command(self, turn_on):
        """Send a standalone electromagnet ON/OFF command (manual toggle, no place sequence)."""
        if self._em_goal_in_flight:
            self.get_logger().warn("Electromagnet command busy; ignoring manual toggle.")
            self._log("Magnet: command busy, try again.")
            return
        client = None
        controller_name = None
        for name, c in (
            ("tool_controller", self._em_tool_action_client),
            ("magnet_controller", self._em_magnet_action_client),
        ):
            if c.wait_for_server(timeout_sec=0.2):
                client = c
                controller_name = name
                break
        if client is None:
            self.get_logger().warn("Electromagnet action server not available.")
            self._log("Magnet: server not available.")
            return
        self._em_goal_in_flight = True
        target_pwm = 1.0 if turn_on else 0.0
        goal_msg = FollowJointTrajectory.Goal()
        goal_msg.trajectory = JointTrajectory()
        goal_msg.trajectory.joint_names = ["jointPWM"]
        point = JointTrajectoryPoint()
        point.positions = [target_pwm]
        point.time_from_start = RosDuration(sec=0, nanosec=500_000_000)  # 0.5s
        goal_msg.trajectory.points = [point]
        self._log("Manual magnet %s via %s" % ("ON" if turn_on else "OFF", controller_name))
        self._set_robot_pose_status(
            "(electromagnet %s)" % ("ON" if turn_on else "OFF"),
            "Electromagnet command...",
        )
        send_future = client.send_goal_async(goal_msg)
        send_future.add_done_callback(lambda f: self._manual_em_goal_response_callback(f, turn_on))

    def _manual_em_goal_response_callback(self, future, turn_on):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Manual magnet goal rejected")
            self._em_goal_in_flight = False
            self._schedule_update_magnet_button()
            return
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(lambda f: self._manual_em_result_callback(f, turn_on))

    def _manual_em_result_callback(self, future, turn_on):
        response = future.result()
        status = getattr(response, "status", None)
        succeeded = (status == GoalStatus.STATUS_SUCCEEDED) if status is not None else True
        self._em_goal_in_flight = False
        if succeeded:
            self._manual_em_last_state = turn_on
            self.get_logger().info("Manual magnet turned %s" % ("ON" if turn_on else "OFF"))
            self._log("Magnet: %s." % ("ON" if turn_on else "OFF"))
        else:
            self.get_logger().warn("Manual magnet command failed (status=%s)" % status)
            self._log("Magnet: command failed.")
        self._schedule_update_magnet_button()

    def _schedule_update_magnet_button(self):
        """Update magnet toggle button label on the GUI thread."""
        if self._root and self._root.winfo_exists() and getattr(self, "_magnet_toggle_btn", None):
            self._root.after(0, self._update_magnet_toggle_button)

    def _update_magnet_toggle_button(self):
        if getattr(self, "_magnet_toggle_btn", None) and self._magnet_toggle_btn.winfo_exists():
            self._magnet_toggle_btn.config(text="Magnet ON" if self._manual_em_last_state else "Magnet OFF")

    def _on_manual_toggle_magnet(self):
        """Toggle electromagnet ON/OFF via manual button."""
        turn_on = not self._manual_em_last_state
        self._send_manual_em_command(turn_on)

    def _robot_em_goal_response_callback(self, future, turn_on, step_for_logging):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot magnet goal rejected")
            self._em_goal_in_flight = False
            # Advance sequence anyway
            self._robot_move_step += 1
            self._log(
                "Robot magnet step %d/%d completed (rejected)."
                % (self._robot_move_step, self._ROBOT_PLACE_NUM_STEPS)
            )
            if self._robot_move_step >= self._ROBOT_PLACE_NUM_STEPS:
                from_wp = self._robot_move_pick
                to_wp = self._robot_move_place
                self._robot_move_pick = self._robot_move_place = None
                self._robot_move_step = 0
                self._robot_sequence_busy = False
                self._manual_em_last_state = False
                self._schedule_update_magnet_button()
                if self._reset_return_queue is not None:
                    for i in range(5):
                        if self._red_piece_locations[i] == from_wp:
                            self._red_piece_locations[i] = to_wp
                            break
                        if self._blue_piece_locations[i] == from_wp:
                            self._blue_piece_locations[i] = to_wp
                            break
                    self._update_piece_locations_display()
                    if self._reset_return_queue:
                        from_next, to_next = self._reset_return_queue.pop(0)
                        self._robot_move_pick = from_next
                        self._robot_move_place = to_next
                        self._robot_move_step = 0
                        self._robot_sequence_busy = True
                        self._log("Robot: reset - returning %s -> %s" % (from_next, to_next))
                        if self._root and self._root.winfo_exists():
                            self._root.after(250, self._robot_place_piece_step)
                        else:
                            self._robot_place_piece_step()
                    else:
                        self._reset_return_queue = None
                        self._log("Reset: all pieces returned (magnet rejected). Resetting game.")
                        self._do_logical_reset()
                else:
                    self.get_logger().info("Robot placed piece; at MID, waiting for next command.")
                    self._log("Robot: piece placed, at MID (magnet off), waiting for next command.")
                self._set_robot_pose_status("(at MID, magnet off)", "Done: at MID, waiting for next command.")
                return
            if self._root and self._root.winfo_exists():
                self._root.after(250, self._robot_place_piece_step)
            else:
                self._robot_place_piece_step()
            return

        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(lambda f: self._robot_em_result_callback(f, turn_on, step_for_logging))

    def _robot_em_result_callback(self, future, turn_on, step_for_logging):
        response = future.result()
        status = getattr(response, "status", None)
        succeeded = (status == GoalStatus.STATUS_SUCCEEDED) if status is not None else True
        self._em_goal_in_flight = False
        if succeeded:
            self.get_logger().info("Robot magnet turned %s" % ("ON" if turn_on else "OFF"))
            self._log(
                "Robot magnet step %d/%d completed."
                % (step_for_logging + 1, self._ROBOT_PLACE_NUM_STEPS)
            )
        else:
            self.get_logger().warn("Robot magnet command failed (status=%s)" % status)
            self._log(
                "Robot magnet step %d/%d completed (failed)."
                % (step_for_logging + 1, self._ROBOT_PLACE_NUM_STEPS)
            )

        # Advance sequence
        self._robot_move_step += 1
        if self._robot_move_step >= self._ROBOT_PLACE_NUM_STEPS:
            from_wp = self._robot_move_pick
            to_wp = self._robot_move_place
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            self._manual_em_last_state = False  # sequence ends with magnet OFF
            self._schedule_update_magnet_button()
            # If we were in reset mode: update piece location and run next return or finish reset
            if self._reset_return_queue is not None:
                for i in range(5):
                    if self._red_piece_locations[i] == from_wp:
                        self._red_piece_locations[i] = to_wp
                        break
                    if self._blue_piece_locations[i] == from_wp:
                        self._blue_piece_locations[i] = to_wp
                        break
                self._update_piece_locations_display()
                if self._reset_return_queue:
                    from_next, to_next = self._reset_return_queue.pop(0)
                    self._robot_move_pick = from_next
                    self._robot_move_place = to_next
                    self._robot_move_step = 0
                    self._robot_sequence_busy = True
                    self._log("Robot: reset - returning %s -> %s" % (from_next, to_next))
                    if self._root and self._root.winfo_exists():
                        self._root.after(250, self._robot_place_piece_step)
                    else:
                        self._robot_place_piece_step()
                else:
                    self._reset_return_queue = None
                    self.get_logger().info("Robot finished returning all pieces; resetting game.")
                    self._log("Reset: all pieces returned. Resetting game.")
                    self._do_logical_reset()
                self._set_robot_pose_status("(at MID, magnet off)", "Done: at MID, waiting for next command.")
                return
            self.get_logger().info("Robot placed piece; at MID, waiting for next command.")
            self._log("Robot: piece placed, at MID (magnet off), waiting for next command.")
            # If we were waiting to switch turns (2P mode), do it now.
            if self._pending_turn_value is not None and self._pending_turn_command is not None:
                self._turn = self._pending_turn_value
                self._send_command(self._pending_turn_command)
                self._pending_turn_value = None
                self._pending_turn_command = None
                self._update_status()
            self._set_robot_pose_status("(at MID, magnet off)", "Done: at MID, waiting for next command.")
            return
        if self._root and self._root.winfo_exists():
            self._root.after(250, self._robot_place_piece_step)
        else:
            self._robot_place_piece_step()

    def _robot_place_piece_step(self):
        """Pick/place sequence (10 steps). Heights are +Z offsets (m) on waypoint z from the GUI.

        0–1: hover then lower to pickup (magnet off) · 2: magnet ON · 3: pick hover (magnet on) ·
        4: transit over board · 5: hover over drop · 6: drop height (magnet off) · 7: magnet OFF ·
        8: MID · 9: magnet OFF at MID.
        """
        if self._robot_move_pick is None or self._robot_move_place is None:
            return
        step = self._robot_move_step
        N = self._ROBOT_PLACE_NUM_STEPS
        # Magnet-only steps (guarantee ON/OFF independent of GoToPose server PWM handling)
        if step == 2:
            self._robot_send_em_command_async(True, step)
            return
        if step in (7, 9):
            self._robot_send_em_command_async(False, step)
            return

        hover_m, pickup_m, transit_m, drop_m = self._get_piece_heights_m()

        if step == 0:
            wp_name = self._robot_move_pick + "_hover"
            magnet_on = False
            pose = self._waypoint_pose(self._robot_move_pick)
            if pose:
                pose.pose.position.z += hover_m
        elif step == 1:
            wp_name = self._robot_move_pick + "_pickup"
            magnet_on = False
            pose = self._waypoint_pose(self._robot_move_pick)
            if pose:
                pose.pose.position.z += pickup_m
        elif step == 3:
            wp_name = self._robot_move_pick + "_hover_carry"
            magnet_on = True
            pose = self._waypoint_pose(self._robot_move_pick)
            if pose:
                pose.pose.position.z += hover_m
        elif step == 4:
            wp_name = self._robot_move_place + "_transit"
            magnet_on = True
            pose = self._waypoint_pose(self._robot_move_place)
            if pose:
                pose.pose.position.z += transit_m
        elif step == 5:
            wp_name = self._robot_move_place + "_hover_drop"
            magnet_on = True
            pose = self._waypoint_pose(self._robot_move_place)
            if pose:
                pose.pose.position.z += hover_m
        elif step == 6:
            wp_name = self._robot_move_place + "_drop"
            magnet_on = False
            pose = self._waypoint_pose(self._robot_move_place)
            if pose:
                pose.pose.position.z += drop_m
        elif step == 8:
            wp_name = 'MID'
            magnet_on = False
            pose = self._waypoint_pose('MID')
        elif step == 9:
            wp_name = 'MID_off'
            magnet_on = False
            pose = self._waypoint_pose('MID')
        else:
            wp_name = '?'
            magnet_on = False
            pose = None

        step_labels = (
            "pick hover over piece (magnet off)",
            "lower to pickup height (magnet off)",
            "magnet ON at pickup",
            "lift to pick hover (magnet on)",
            "transit to drop cell (magnet on)",
            "hover over drop cell (magnet on)",
            "lower to drop height / release (magnet off)",
            "magnet OFF confirm",
            "return to MID (magnet off)",
            "magnet OFF at MID",
        )

        if not pose:
            self.get_logger().warn("Robot move: waypoint '%s' not found" % wp_name)
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            if self._reset_return_queue is not None:
                self._reset_return_queue = None
                self._log("Reset aborted: waypoint '%s' not found." % wp_name)
                self._do_logical_reset()
            else:
                self._set_robot_pose_status("waypoint '%s' not in config" % wp_name, "Aborted: waypoint not found")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().warn("Robot move: go_to_pose server not available")
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            self._pose_goal_in_flight = False
            if self._reset_return_queue is not None:
                self._reset_return_queue = None
                self._log("Reset aborted: go_to_pose server not available.")
                self._do_logical_reset()
            else:
                self._set_robot_pose_status("go_to_pose action server not available", "Aborted: server not available")
            return
        if self._pose_goal_in_flight:
            return
        self._pose_goal_in_flight = True
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = magnet_on
        p = pose.pose.position
        details = (
            "waypoint=%s  frame=%s  x=%.3f  y=%.3f  z=%.3f  electromagnet=%s  "
            "pos_tol=%.3fm  timeout=%.1fs  [step %d/%d: %s]"
        ) % (
            wp_name,
            pose.header.frame_id,
            p.x,
            p.y,
            p.z,
            "ON" if magnet_on else "OFF",
            0.01,
            15.0,
            step + 1,
            N,
            step_labels[step],
        )
        self._set_robot_pose_status(details, "Moving... (step %d/%d)" % (step + 1, N))
        self._log(
            "Robot pose step %d/%d: waypoint=%s  x=%.3f  y=%.3f  z=%.3f  magnet=%s  [%s]"
            % (
                step + 1,
                N,
                wp_name,
                p.x,
                p.y,
                p.z,
                "ON" if magnet_on else "OFF",
                step_labels[step],
            )
        )
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._robot_place_goal_response_callback)

    def _robot_place_goal_response_callback(self, future):
        """Handle send_goal_async result; on accept, wait for result and then advance step."""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot place: goal rejected")
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            self._pose_goal_in_flight = False
            if self._reset_return_queue is not None:
                self._reset_return_queue = None
                self._log("Reset aborted: goal rejected.")
                self._do_logical_reset()
            else:
                self._set_robot_pose_status("(goal was rejected by action server)", "Goal rejected")
            return
        self._set_robot_pose_status("(see above)", "Goal accepted, executing...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._robot_place_result_callback)

    def _robot_place_result_callback(self, future):
        """After each step: advance or finish. Next step only runs after this command finished."""
        result = future.result().result
        self._pose_goal_in_flight = False
        if not result.success:
            msg = getattr(result, 'message', '') or 'Unknown error'
            self.get_logger().warn("Robot place step failed: %s" % msg)
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            if self._reset_return_queue is not None:
                self._reset_return_queue = None
                self._log("Reset aborted: %s" % msg)
                self._do_logical_reset()
            else:
                err_detail = "error_code=%s  final_pos_err=%.4fm  message=%s" % (
                    getattr(result, 'error_code', ''), getattr(result, 'final_pos_error_m', 0), msg)
                self._set_robot_pose_status(err_detail, "Failed: " + msg)
            return
        self._robot_move_step += 1
        self._log(
            "Robot pose step %d/%d completed."
            % (self._robot_move_step, self._ROBOT_PLACE_NUM_STEPS)
        )
        if self._robot_move_step >= self._ROBOT_PLACE_NUM_STEPS:
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            self.get_logger().info("Robot placed piece; at MID, waiting for next command.")
            self._log("Robot: piece placed, at MID (magnet off), waiting for next command.")
            # If we were waiting to switch turns (2P mode), do it now.
            if self._pending_turn_value is not None and self._pending_turn_command is not None:
                self._turn = self._pending_turn_value
                self._send_command(self._pending_turn_command)
                self._pending_turn_value = None
                self._pending_turn_command = None
                self._update_status()
            self._set_robot_pose_status("(at MID, magnet off)", "Done: at MID, waiting for next command.")
            return
        # Pause 250 ms after each pose move, then send next step
        if self._root and self._root.winfo_exists():
            self._root.after(250, self._robot_place_piece_step)
        else:
            self._robot_place_piece_step()

    def _robot_go_home(self):
        """Send robot to HOME waypoint (non-blocking). Called on game reset."""
        if self._robot_is_busy():
            self._log("Robot busy, skipping HOME command.")
            return
        pose = self._waypoint_pose('HOME')
        if not pose:
            self.get_logger().warn("Robot go home: HOME waypoint not found")
            self._set_robot_pose_status("HOME waypoint not in config", "Aborted: HOME not found")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().warn("Robot go home: go_to_pose server not available")
            self._set_robot_pose_status("go_to_pose action server not available", "Aborted: server not available")
            return
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = False
        p = pose.pose.position
        details = (
            "waypoint=HOME  frame=%s  x=%.3f  y=%.3f  z=%.3f  electromagnet=OFF  "
            "pos_tol=0.010m  timeout=15.0s"
        ) % (pose.header.frame_id, p.x, p.y, p.z)
        self._set_robot_pose_status(details, "Moving to HOME...")
        self._log("Robot pose: waypoint=HOME  x=%.3f  y=%.3f  z=%.3f" % (p.x, p.y, p.z))
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._robot_go_home_response_callback)

    def _robot_go_home_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot go home: goal rejected")
            self._set_robot_pose_status("(goal was rejected by action server)", "Goal rejected")
            return
        self._set_robot_pose_status("(see above)", "Goal accepted, executing...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._robot_go_home_result_callback)

    def _robot_go_home_result_callback(self, future):
        result = future.result().result
        if result.success:
            self.get_logger().info("Robot at HOME.")
            self._set_robot_pose_status("(last goal: HOME)", "Done: at HOME.")
            self._schedule_manual_xyz_update_from_tf()
        else:
            msg = getattr(result, 'message', '') or 'Unknown error'
            self.get_logger().warn("Robot go home failed: %s" % msg)
            err_detail = "error_code=%s  final_pos_err=%.4fm  message=%s" % (
                getattr(result, 'error_code', ''), getattr(result, 'final_pos_error_m', 0), msg)
            self._set_robot_pose_status(err_detail, "Failed: " + msg)

    def _robot_go_mid(self):
        """Send robot to MID waypoint (non-blocking). For manual control."""
        if self._robot_is_busy():
            self._set_robot_pose_status("Robot busy (finish current move first)", "Blocked: robot busy")
            return
        pose = self._waypoint_pose('MID')
        if not pose:
            self.get_logger().warn("Robot go MID: MID waypoint not found")
            self._set_robot_pose_status("MID waypoint not in config", "Aborted: MID not found")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().warn("Robot go MID: go_to_pose server not available")
            self._set_robot_pose_status("go_to_pose action server not available", "Aborted: server not available")
            return
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = False
        p = pose.pose.position
        details = (
            "waypoint=MID  frame=%s  x=%.3f  y=%.3f  z=%.3f  electromagnet=OFF  "
            "pos_tol=0.010m  timeout=15.0s"
        ) % (pose.header.frame_id, p.x, p.y, p.z)
        self._set_robot_pose_status(details, "Moving to MID...")
        self._log("Robot pose: waypoint=MID  x=%.3f  y=%.3f  z=%.3f" % (p.x, p.y, p.z))
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._robot_go_mid_response_callback)

    def _robot_go_mid_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot go MID: goal rejected")
            self._set_robot_pose_status("(goal was rejected by action server)", "Goal rejected")
            return
        self._set_robot_pose_status("(see above)", "Goal accepted, executing...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._robot_go_mid_result_callback)

    def _robot_go_mid_result_callback(self, future):
        result = future.result().result
        if result.success:
            self.get_logger().info("Robot at MID.")
            self._set_robot_pose_status("(last goal: MID)", "Done: at MID.")
            self._schedule_manual_xyz_update_from_tf()
        else:
            msg = getattr(result, 'message', '') or 'Unknown error'
            self.get_logger().warn("Robot go MID failed: %s" % msg)
            err_detail = "error_code=%s  final_pos_err=%.4fm  message=%s" % (
                getattr(result, 'error_code', ''), getattr(result, 'final_pos_error_m', 0), msg)
            self._set_robot_pose_status(err_detail, "Failed: " + msg)

    def _try_robot_idle_mid(self):
        """When not running a pick/place sequence, move to MID (waiting pose)."""
        if self._robot_is_busy():
            return
        if 'MID' not in self._waypoints:
            return
        self._robot_go_mid()

    def _on_manual_move(self):
        """Move robot to user-entered x, y, z (frame base_link)."""
        if self._robot_is_busy():
            self._set_robot_pose_status("Robot busy (finish current move first)", "Blocked: robot busy")
            return
        try:
            x = float(self._manual_x_var.get().strip())
            y = float(self._manual_y_var.get().strip())
            z = float(self._manual_z_var.get().strip())
        except ValueError:
            self._set_robot_pose_status("Invalid x, y, z (enter numbers)", "Error: invalid input")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self._set_robot_pose_status("go_to_pose action server not available", "Aborted: server not available")
            return
        pose = PoseStamped()
        pose.header.frame_id = 'base_link'
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.pose.position = Point(x=x, y=y, z=z)
        pose.pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = False
        details = (
            "manual  frame=base_link  x=%.3f  y=%.3f  z=%.3f  electromagnet=OFF  "
            "pos_tol=0.010m  timeout=15.0s"
        ) % (x, y, z)
        self._set_robot_pose_status(details, "Moving to (%.3f, %.3f, %.3f)..." % (x, y, z))
        self._log("Robot pose (manual): x=%.3f  y=%.3f  z=%.3f" % (x, y, z))
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._manual_move_response_callback)

    def _on_manual_jog(self, axis, direction):
        """Jog a single axis using +/- buttons (direction is +/-1)."""
        axis = (axis or '').strip().lower()
        direction = float(direction)
        if axis not in ('x', 'y', 'z') or direction == 0.0:
            return
        try:
            step_m = float(self._manual_jog_step_m_var.get().strip())
        except (ValueError, AttributeError):
            step_m = 0.005
        if step_m == 0.0:
            return

        var = None
        if axis == 'x':
            var = self._manual_x_var
        elif axis == 'y':
            var = self._manual_y_var
        else:
            var = self._manual_z_var

        try:
            cur = float(var.get().strip())
        except (ValueError, AttributeError):
            return

        new_val = cur + (direction * step_m)

        # Keep display short but precise enough for meters.
        s = f"{new_val:.6f}".rstrip('0').rstrip('.')
        if s == '':
            s = '0'
        var.set(s)

        # Send updated target immediately.
        self._on_manual_move()

    def _manual_move_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self._set_robot_pose_status("(goal was rejected by action server)", "Goal rejected")
            return
        self._set_robot_pose_status("(see above)", "Goal accepted, executing...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._manual_move_result_callback)

    def _manual_move_result_callback(self, future):
        result = future.result().result
        if result.success:
            self._set_robot_pose_status("(last goal: manual pose)", "Done: moved to target.")
        else:
            msg = getattr(result, 'message', '') or 'Unknown error'
            err_detail = "error_code=%s  final_pos_err=%.4fm  message=%s" % (
                getattr(result, 'error_code', ''), getattr(result, 'final_pos_error_m', 0), msg)
            self._set_robot_pose_status(err_detail, "Failed: " + msg)

    def _calib_pickup_waypoint_name(self):
        color = (self._calib_piece_color_var.get() or '').strip().lower()
        slot = (self._calib_pickup_slot_var.get() or '').strip()
        prefix = 'R' if color in ('red', 'r', 'x') else 'B'
        return f"{prefix}{slot}"

    def _calib_drop_waypoint_name(self):
        cell = (self._calib_drop_cell_var.get() or '').strip()
        return f"T{cell}"

    def _get_manual_xyz_m(self):
        x = float(self._manual_x_var.get().strip())
        y = float(self._manual_y_var.get().strip())
        z = float(self._manual_z_var.get().strip())
        return x, y, z

    def _calib_move_to_waypoint(self, waypoint_name):
        """Move robot to a waypoint pose (magnet OFF) for calibration positioning."""
        if self._robot_is_busy():
            self._set_robot_pose_status("Robot busy (finish current move first)", "Blocked: robot busy")
            return
        pose = self._waypoint_pose(waypoint_name)
        if not pose:
            self.get_logger().warn("Calibration move: waypoint '%s' not found" % waypoint_name)
            self._set_robot_pose_status("Waypoint not in config: %s" % waypoint_name, "Error")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self._set_robot_pose_status("go_to_pose action server not available", "Aborted")
            return

        self._calib_move_last_waypoint = waypoint_name
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = False

        p = pose.pose.position
        # Update manual XYZ boxes to target waypoint so user sees where we're moving
        self._manual_x_var.set("%.3f" % p.x)
        self._manual_y_var.set("%.3f" % p.y)
        self._manual_z_var.set("%.3f" % p.z)
        details = (
            "calib move  waypoint=%s  frame=%s  x=%.3f  y=%.3f  z=%.3f  electromagnet=OFF"
            % (waypoint_name, pose.header.frame_id, p.x, p.y, p.z)
        )
        self._set_robot_pose_status(details, "Moving for calibration...")
        self._log(details)
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._calib_move_response_callback)

    def _calib_move_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self._set_robot_pose_status("(goal was rejected by action server)", "Calibration move rejected")
            return
        self._set_robot_pose_status("(see above)", "Calibration goal accepted, executing...")
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._calib_move_result_callback)

    def _calib_move_result_callback(self, future):
        result = future.result().result
        if result.success:
            wp = getattr(self, '_calib_move_last_waypoint', 'waypoint')
            self._set_robot_pose_status("(last goal: %s)" % wp, "Done: calibration move.")
            # Refresh manual coordinates from TF on main thread
            self._schedule_manual_xyz_update_from_tf()
        else:
            msg = getattr(result, 'message', '') or 'Unknown error'
            err_detail = "error_code=%s  final_pos_err=%.4fm  message=%s" % (
                getattr(result, 'error_code', ''), getattr(result, 'final_pos_error_m', 0), msg)
            self._set_robot_pose_status(err_detail, "Failed: calibration move")

    def _save_calibrated_waypoint(self, waypoint_name):
        """Save XYZ (from Manual move fields) into waypoint_name, then persist to YAML + reload."""
        try:
            x_m, y_m, z_m = self._get_manual_xyz_m()
        except Exception:
            self._set_robot_pose_status("Invalid XYZ (enter numeric values in meters).", "Error")
            return

        try:
            self._update_waypoint_xyz(waypoint_name, x_m, y_m, z_m)
            self._persist_waypoints()
        except Exception as e:
            self.get_logger().warn("Calibration save failed: %s" % e)
            messagebox.showerror("Save failed", "Could not save waypoint to waypoints.yaml:\n%s" % e)
            return

        self._load_waypoints()
        self.get_logger().info("Saved waypoint '%s' to waypoints.yaml." % waypoint_name)
        if getattr(self, '_log_text', None) is not None:
            self._log("Saved waypoint: %s  {x=%.3f, y=%.3f, z=%.3f}" % (waypoint_name, x_m, y_m, z_m))
            self._log_waypoints()
        self._set_robot_pose_status("Saved %s to waypoints.yaml" % waypoint_name, "Done")

    def _save_calibrated_waypoint_from_current_pose(self, waypoint_name):
        """Save XYZ from the robot's current TF pose into waypoint_name, then persist to YAML + reload."""
        pose = self._get_current_pose_from_tf(warn_on_fail=True)
        if not pose:
            self._set_robot_pose_status("Could not read current pose from TF", "Error")
            return
        x_m = pose.pose.position.x
        y_m = pose.pose.position.y
        z_m = pose.pose.position.z

        try:
            self._update_waypoint_xyz(waypoint_name, x_m, y_m, z_m)
            self._persist_waypoints()
        except Exception as e:
            self.get_logger().warn("Calibration save from current pose failed: %s" % e)
            messagebox.showerror("Save failed", "Could not save waypoint to waypoints.yaml:\n%s" % e)
            return

        self._load_waypoints()
        self.get_logger().info("Saved waypoint '%s' from current pose." % waypoint_name)
        if getattr(self, '_log_text', None) is not None:
            self._log("Saved waypoint from current pose: %s  {x=%.3f, y=%.3f, z=%.3f}" % (waypoint_name, x_m, y_m, z_m))
            self._log_waypoints()
        self._set_robot_pose_status("Saved %s from current pose to waypoints.yaml" % waypoint_name, "Done")

    def _schedule_manual_xyz_realtime_update(self):
        """Schedule periodic TF->manual XYZ sync."""
        if not self._root or not self._root.winfo_exists():
            return
        if self._manual_xyz_realtime_enabled:
            self._manual_xyz_after_id = self._root.after(200, self._update_manual_xyz_realtime)

    def _schedule_manual_xyz_update_from_tf(self):
        """Schedule a single force-update of manual XYZ from TF on the main thread.
        Safe to call from ROS action callbacks (which run on executor thread).
        """
        if self._root and self._root.winfo_exists():
            self._root.after(0, lambda: self._update_manual_xyz_realtime(force=True))

    def _update_manual_xyz_realtime(self, force=False):
        """Update manual move X/Y/Z boxes from the current end-effector TF pose."""
        if not self._root or not self._root.winfo_exists():
            return
        if not getattr(self, '_manual_xyz_realtime_enabled', False):
            return

        focus = None
        try:
            focus = self._root.focus_get()
        except (tk.TclError, KeyError):
            focus = None

        # Don't overwrite values while the user is actively typing in an entry,
        # unless we explicitly force an update (e.g., after Reset).
        if not force and focus in (
            getattr(self, '_manual_x_entry', None),
            getattr(self, '_manual_y_entry', None),
            getattr(self, '_manual_z_entry', None),
        ):
            self._schedule_manual_xyz_realtime_update()
            return

        pose = self._get_current_pose_from_tf(warn_on_fail=False)
        if pose:
            x_m = pose.pose.position.x
            y_m = pose.pose.position.y
            z_m = pose.pose.position.z
            self._manual_x_var.set(f"{x_m:.3f}")
            self._manual_y_var.set(f"{y_m:.3f}")
            self._manual_z_var.set(f"{z_m:.3f}")

        self._schedule_manual_xyz_realtime_update()

    def _on_calib_move_pickup(self):
        self._calib_move_to_waypoint(self._calib_pickup_waypoint_name())

    def _on_calib_move_drop(self):
        self._calib_move_to_waypoint(self._calib_drop_waypoint_name())

    def _on_test_move_t04(self):
        """Test: move arm to board waypoint T04 (magnet off)."""
        self._calib_move_to_waypoint('T04')

    def _on_calib_save_pickup(self):
        self._save_calibrated_waypoint(self._calib_pickup_waypoint_name())

    def _on_calib_save_drop(self):
        self._save_calibrated_waypoint(self._calib_drop_waypoint_name())

    def _on_calib_save_pickup_from_current(self):
        self._save_calibrated_waypoint_from_current_pose(self._calib_pickup_waypoint_name())

    def _on_calib_save_drop_from_current(self):
        self._save_calibrated_waypoint_from_current_pose(self._calib_drop_waypoint_name())

    def _on_calib_test_pick_place(self):
        """One-time physical test: pick selected piece and place on selected board cell."""
        if self._robot_is_busy():
            self._set_robot_pose_status("Robot busy (finish current move first)", "Blocked: robot busy")
            return
        pick_wp = self._calib_pickup_waypoint_name()
        drop_wp = self._calib_drop_waypoint_name()
        if not self._waypoint_pose(pick_wp) or not self._waypoint_pose(drop_wp):
            self._set_robot_pose_status("Waypoint(s) not in config.", "Error")
            return

        self._robot_move_pick = pick_wp
        self._robot_move_place = drop_wp
        self._robot_move_step = 0
        self._robot_sequence_busy = True
        self._log("Calibration test: place %s -> %s" % (pick_wp, drop_wp))
        self._set_robot_pose_status("Calibration test: pick->place (%s -> %s)" % (pick_wp, drop_wp), "Starting...")
        self._robot_place_piece_step()

    def _build_gui(self):
        self._root = tk.Tk()
        self._root.title("Macropad Tic-Tac-Toe")
        self._root.geometry("520x430")
        self._root.resizable(True, True)

        main = ttk.Frame(self._root, padding=10)
        main.pack(fill=tk.BOTH, expand=True)

        # Connection
        conn = ttk.LabelFrame(main, text="Connection", padding=6)
        conn.pack(fill=tk.X, pady=(0, 6))
        ttk.Label(conn, text="Port:").pack(side=tk.LEFT, padx=(0, 4))
        port_var = tk.StringVar()
        self._port_combo = ttk.Combobox(conn, textvariable=port_var, width=28, state="normal")
        self._port_combo.pack(side=tk.LEFT, padx=(0, 8))
        if serial and list_serial_ports():
            ports = list_serial_ports()
            self._port_combo["values"] = [p[0] for p in ports]
            self._port_combo.set(ports[0][0])
        else:
            self._port_combo.set("/dev/ttyACM1" if __import__("sys").platform != "win32" else "COM1")
        ttk.Label(conn, text="Baud:").pack(side=tk.LEFT, padx=(12, 4))
        baud_var = tk.StringVar(value="115200")
        ttk.Combobox(conn, textvariable=baud_var, width=8, state="readonly",
                     values=("9600", "19200", "38400", "57600", "115200", "230400")).pack(side=tk.LEFT, padx=(0, 8))
        self._connect_btn = ttk.Button(conn, text="Connect", command=self._toggle_connect)
        self._connect_btn.pack(side=tk.LEFT, padx=(12, 0))
        self._baud_var = baud_var
        self._port_var = port_var

        # Status
        status_frame = ttk.LabelFrame(main, text="Status", padding=6)
        status_frame.pack(fill=tk.X, pady=(0, 6))
        self._status_var = tk.StringVar(value="Disconnected. Connect and press Reset to start.")
        ttk.Label(status_frame, textvariable=self._status_var, font=("TkDefaultFont", 10)).pack(anchor=tk.W)

        # Game mode and Reset
        ctrl = ttk.Frame(main)
        ctrl.pack(fill=tk.X, pady=(0, 6))
        ttk.Label(ctrl, text="Game mode:").pack(side=tk.LEFT, padx=(0, 6))
        self._mode_combo = ttk.Combobox(
            ctrl, values=self.GAME_MODES, state="readonly", width=24
        )
        self._mode_combo.pack(side=tk.LEFT, padx=(0, 12))
        self._mode_combo.current(0)
        self._reset_btn = ttk.Button(ctrl, text="Reset game", command=self._on_reset)
        self._reset_btn.pack(side=tk.LEFT, padx=4)
        self._reload_waypoints_btn = ttk.Button(ctrl, text="Reload waypoints", command=self._on_reload_waypoints)
        self._reload_waypoints_btn.pack(side=tk.LEFT, padx=4)

        # Waypoints YAML path override + browse dialog
        ttk.Label(ctrl, text="Waypoints YAML:").pack(side=tk.LEFT, padx=(12, 4))
        self._waypoints_yaml_path_var = tk.StringVar(value=self._default_waypoints_yaml_path())
        ttk.Entry(ctrl, textvariable=self._waypoints_yaml_path_var, width=42).pack(side=tk.LEFT, padx=(0, 6))
        ttk.Button(ctrl, text="Browse...", command=self._on_browse_waypoints_yaml).pack(side=tk.LEFT, padx=(0, 4))

        # Piece locations (red = X, blue = O; R00–R04/B00–B04 = home, T00–T08 = board)
        piece_frame = ttk.LabelFrame(main, text="Piece locations", padding=6)
        piece_frame.pack(fill=tk.X, pady=(0, 6))
        self._red_piece_locations_var = tk.StringVar()
        self._blue_piece_locations_var = tk.StringVar()
        ttk.Label(piece_frame, text="Red (X):", font=("TkDefaultFont", 9)).pack(anchor=tk.W)
        ttk.Label(piece_frame, textvariable=self._red_piece_locations_var, font=("Consolas", 9)).pack(anchor=tk.W)
        ttk.Label(piece_frame, text="Blue (O):", font=("TkDefaultFont", 9)).pack(anchor=tk.W)
        ttk.Label(piece_frame, textvariable=self._blue_piece_locations_var, font=("Consolas", 9)).pack(anchor=tk.W)
        self._update_piece_locations_display()

        # Piece heights (mm): added to waypoint z — hover over pick/drop, grab height, travel, place release
        height_frame = ttk.LabelFrame(main, text="Piece heights (mm, +Z above waypoint z)", padding=6)
        height_frame.pack(fill=tk.X, pady=(0, 6))
        height_row = ttk.Frame(height_frame)
        height_row.pack(fill=tk.X)
        ttk.Label(height_row, text="Hover height:").pack(side=tk.LEFT, padx=(0, 2))
        self._hover_height_mm_var = tk.StringVar(value="60")
        ttk.Entry(height_row, textvariable=self._hover_height_mm_var, width=6).pack(side=tk.LEFT, padx=(0, 10))
        ttk.Label(height_row, text="Pickup (grab z):").pack(side=tk.LEFT, padx=(0, 2))
        self._pickup_height_mm_var = tk.StringVar(value="0")
        ttk.Entry(height_row, textvariable=self._pickup_height_mm_var, width=6).pack(side=tk.LEFT, padx=(0, 10))
        ttk.Label(height_row, text="Transit height:").pack(side=tk.LEFT, padx=(0, 2))
        self._transit_height_mm_var = tk.StringVar(value="60")
        ttk.Entry(height_row, textvariable=self._transit_height_mm_var, width=6).pack(side=tk.LEFT, padx=(0, 10))
        ttk.Label(height_row, text="Drop height:").pack(side=tk.LEFT, padx=(0, 2))
        self._drop_height_mm_var = tk.StringVar(value="20")
        ttk.Entry(height_row, textvariable=self._drop_height_mm_var, width=6).pack(side=tk.LEFT, padx=(0, 8))

        # Manual move: enter x, y, z and press Move robot
        manual_frame = ttk.LabelFrame(main, text="Manual move", padding=6)
        manual_frame.pack(fill=tk.X, pady=(0, 6))
        manual_row = ttk.Frame(manual_frame)
        manual_row.pack(fill=tk.X)
        ttk.Label(manual_row, text="X:").pack(side=tk.LEFT, padx=(0, 2))
        self._manual_x_var = tk.StringVar(value="0.20")
        self._manual_x_entry = ttk.Entry(manual_row, textvariable=self._manual_x_var, width=8)
        self._manual_x_entry.pack(side=tk.LEFT, padx=(0, 8))
        ttk.Label(manual_row, text="Y:").pack(side=tk.LEFT, padx=(0, 2))
        self._manual_y_var = tk.StringVar(value="0.00")
        self._manual_y_entry = ttk.Entry(manual_row, textvariable=self._manual_y_var, width=8)
        self._manual_y_entry.pack(side=tk.LEFT, padx=(0, 8))
        ttk.Label(manual_row, text="Z:").pack(side=tk.LEFT, padx=(0, 2))
        self._manual_z_var = tk.StringVar(value="0.15")
        self._manual_z_entry = ttk.Entry(manual_row, textvariable=self._manual_z_var, width=8)
        self._manual_z_entry.pack(side=tk.LEFT, padx=(0, 8))
        self._manual_move_btn = ttk.Button(manual_row, text="Move robot", command=self._on_manual_move)
        self._manual_move_btn.pack(side=tk.LEFT, padx=(12, 0))
        ttk.Button(manual_row, text="Home", command=self._robot_go_home).pack(side=tk.LEFT, padx=(8, 0))
        ttk.Button(manual_row, text="MID", command=self._robot_go_mid).pack(side=tk.LEFT, padx=(4, 0))
        ttk.Button(manual_row, text="Test T04", command=self._on_test_move_t04).pack(side=tk.LEFT, padx=(6, 0))
        self._magnet_toggle_btn = ttk.Button(
            manual_row, text="Magnet OFF", command=self._on_manual_toggle_magnet
        )
        self._magnet_toggle_btn.pack(side=tk.LEFT, padx=(8, 0))

        # +/- jog buttons for each axis
        jog_row = ttk.Frame(manual_frame)
        jog_row.pack(fill=tk.X, pady=(6, 0))
        ttk.Label(jog_row, text="Jog step (m):").pack(side=tk.LEFT, padx=(0, 4))
        self._manual_jog_step_m_var = tk.StringVar(value="0.005")
        ttk.Entry(jog_row, textvariable=self._manual_jog_step_m_var, width=8).pack(side=tk.LEFT, padx=(0, 12))

        jog_btns = ttk.Frame(jog_row)
        jog_btns.pack(side=tk.LEFT)
        # X
        ttk.Button(jog_btns, text="X-", width=4, command=lambda: self._on_manual_jog('x', -1)).grid(row=0, column=0, padx=(0, 6))
        ttk.Button(jog_btns, text="X+", width=4, command=lambda: self._on_manual_jog('x', +1)).grid(row=0, column=1, padx=(0, 12))
        # Y
        ttk.Button(jog_btns, text="Y-", width=4, command=lambda: self._on_manual_jog('y', -1)).grid(row=0, column=2, padx=(0, 6))
        ttk.Button(jog_btns, text="Y+", width=4, command=lambda: self._on_manual_jog('y', +1)).grid(row=0, column=3, padx=(0, 12))
        # Z
        ttk.Button(jog_btns, text="Z-", width=4, command=lambda: self._on_manual_jog('z', -1)).grid(row=0, column=4, padx=(0, 6))
        ttk.Button(jog_btns, text="Z+", width=4, command=lambda: self._on_manual_jog('z', +1)).grid(row=0, column=5)

        # Waypoint calibration: save pickup and drop xyz coordinates into waypoints.yaml
        calib_frame = ttk.LabelFrame(main, text="Waypoint calibration (save to waypoints.yaml)", padding=6)
        calib_frame.pack(fill=tk.X, pady=(0, 6))

        calib_sel_row = ttk.Frame(calib_frame)
        calib_sel_row.pack(fill=tk.X)
        ttk.Label(calib_sel_row, text="Pickup piece:").pack(side=tk.LEFT, padx=(0, 6))
        self._calib_piece_color_var = tk.StringVar(value="red")
        ttk.Radiobutton(calib_sel_row, text="Red (X)", value="red", variable=self._calib_piece_color_var).pack(side=tk.LEFT)
        ttk.Radiobutton(calib_sel_row, text="Blue (O)", value="blue", variable=self._calib_piece_color_var).pack(side=tk.LEFT, padx=(12, 0))
        ttk.Label(calib_sel_row, text="Slot:").pack(side=tk.LEFT, padx=(12, 2))
        self._calib_pickup_slot_var = tk.StringVar(value="00")
        ttk.Combobox(
            calib_sel_row,
            textvariable=self._calib_pickup_slot_var,
            values=["00", "01", "02", "03", "04"],
            state="readonly",
            width=4,
        ).pack(side=tk.LEFT, padx=(0, 10))
        ttk.Label(calib_sel_row, text="Drop cell:").pack(side=tk.LEFT, padx=(0, 2))
        self._calib_drop_cell_var = tk.StringVar(value="00")
        ttk.Combobox(
            calib_sel_row,
            textvariable=self._calib_drop_cell_var,
            values=["00", "01", "02", "03", "04", "05", "06", "07", "08"],
            state="readonly",
            width=4,
        ).pack(side=tk.LEFT)

        ttk.Label(calib_frame, text="Use Manual move to jog, then save from current pose.", font=("TkDefaultFont", 9)).pack(
            anchor=tk.W, pady=(6, 0)
        )

        calib_move_row = ttk.Frame(calib_frame)
        calib_move_row.pack(fill=tk.X, pady=(6, 0))
        ttk.Button(calib_move_row, text="Move to pickup wp", command=self._on_calib_move_pickup).pack(side=tk.LEFT, padx=(0, 8))
        ttk.Button(calib_move_row, text="Move to drop wp", command=self._on_calib_move_drop).pack(side=tk.LEFT, padx=(0, 8))

        calib_save_row = ttk.Frame(calib_frame)
        calib_save_row.pack(fill=tk.X, pady=(6, 0))
        ttk.Button(calib_save_row, text="Save pickup from XYZ", command=self._on_calib_save_pickup).pack(side=tk.LEFT, padx=(0, 8))
        ttk.Button(calib_save_row, text="Save drop from XYZ", command=self._on_calib_save_drop).pack(side=tk.LEFT, padx=(0, 8))
        ttk.Button(
            calib_save_row,
            text="Save pickup from current",
            command=self._on_calib_save_pickup_from_current,
        ).pack(side=tk.LEFT, padx=(0, 8))
        ttk.Button(
            calib_save_row,
            text="Save drop from current",
            command=self._on_calib_save_drop_from_current,
        ).pack(side=tk.LEFT, padx=(0, 8))

        calib_test_row = ttk.Frame(calib_frame)
        calib_test_row.pack(fill=tk.X, pady=(6, 0))
        ttk.Button(
            calib_test_row,
            text="Test pick & place (no game)",
            command=self._on_calib_test_pick_place,
        ).pack(side=tk.LEFT)

        # Robot pose / move status (GoToPose goals sent and their status)
        robot_frame = ttk.LabelFrame(main, text="Robot move status", padding=6)
        robot_frame.pack(fill=tk.X, pady=(0, 6))
        self._robot_pose_details_var = tk.StringVar(value="—")
        self._robot_status_var = tk.StringVar(value="Idle")
        ttk.Label(robot_frame, text="Pose / goal:", font=("TkDefaultFont", 9)).pack(anchor=tk.W)
        self._robot_pose_details_label = ttk.Label(
            robot_frame, textvariable=self._robot_pose_details_var,
            font=("Consolas", 9), wraplength=480
        )
        self._robot_pose_details_label.pack(anchor=tk.W)
        ttk.Label(robot_frame, text="Status:", font=("TkDefaultFont", 9)).pack(anchor=tk.W)
        ttk.Label(robot_frame, textvariable=self._robot_status_var, font=("Consolas", 9)).pack(anchor=tk.W)

        # Log
        ttk.Label(main, text="Log:").pack(anchor=tk.W)
        self._log_text = scrolledtext.ScrolledText(main, height=8, font=("Consolas", 9), state=tk.DISABLED)
        self._log_text.pack(fill=tk.BOTH, expand=True, pady=(2, 0))

        self._root.protocol("WM_DELETE_WINDOW", self._on_close)
        self._log_waypoints()

        # Realtime sync: keep manual X/Y/Z entries showing current TF pose.
        self._manual_xyz_realtime_enabled = True
        self._manual_xyz_after_id = None
        self._schedule_manual_xyz_realtime_update()

    def _log(self, msg):
        self._log_text.config(state=tk.NORMAL)
        self._log_text.insert(tk.END, msg + "\n")
        self._log_text.see(tk.END)
        self._log_text.config(state=tk.DISABLED)

    def _log_waypoints(self):
        """Display loaded waypoints (config/waypoints.yaml) in the log box."""
        self._log("--- waypoints (config/waypoints.yaml) ---")
        if not self._waypoints:
            self._log("(none loaded)")
            return
        for name, pt in sorted(self._waypoints.items()):
            x = pt.get("x", 0)
            y = pt.get("y", 0)
            z = pt.get("z", 0)
            self._log("  %s:  { x: %.2f,  y: %.2f,  z: %.2f }" % (name, x, y, z))
        self._log("--- piece locations (red=X, blue=O) ---")
        self._log("  Red:  %s" % ", ".join(self._red_piece_locations))
        self._log("  Blue: %s" % ", ".join(self._blue_piece_locations))
        self._log("------------------------------------------")

    def _update_status(self):
        if self._ser is None or not self._ser.is_open:
            self._status_var.set("Disconnected. Connect and press Reset to start.")
            return
        # Heartbeat: macropad sends hb99 ~every second; warn if missing for >2.5s
        now = time.monotonic()
        heartbeat_stale = (
            self._last_heartbeat_time is not None
            and (now - self._last_heartbeat_time) > 2.5
        )
        if heartbeat_stale:
            self._status_var.set("Connected — No heartbeat from macropad (check cable/firmware)")
            return
        if self._game_over:
            if self._winner == 'Tie':
                self._status_var.set("Game over: Tie!")
            else:
                self._status_var.set(f"Game over: {self._winner} wins!")
            return
        mode = self.GAME_MODES[self._game_mode_idx]
        self._status_var.set(f"{mode} — Turn: {self._turn} (Red=X, Blue=O)")

    def _update_piece_locations_display(self):
        """Refresh the piece locations shown in the window."""
        if getattr(self, '_red_piece_locations_var', None) is None:
            return
        self._red_piece_locations_var.set("  ".join(self._red_piece_locations))
        self._blue_piece_locations_var.set("  ".join(self._blue_piece_locations))

    def _set_robot_pose_status(self, details_text, status_text):
        """Update robot pose details and status in the GUI (safe to call from any thread)."""
        if getattr(self, '_robot_pose_details_var', None) is None:
            return
        def update():
            self._robot_pose_details_var.set(details_text)
            self._robot_status_var.set(status_text)
        if self._root and self._root.winfo_exists():
            self._root.after(0, update)

    def _toggle_connect(self):
        if self._ser is not None and self._ser.is_open:
            self._disconnect()
        else:
            self._connect()

    def _connect(self):
        if serial is None:
            messagebox.showerror("Error", "Install pyserial: pip install pyserial")
            return
        port = self._port_var.get().strip()
        if not port:
            messagebox.showwarning("Warning", "Enter a port.")
            return
        try:
            baud = int(self._baud_var.get())
        except ValueError:
            baud = 115200
        try:
            self._ser = serial.Serial(port=port, baudrate=baud, timeout=0.05)
            self._reading = True
            self._last_heartbeat_time = time.monotonic()  # consider alive on connect
            self._connect_btn.config(text="Disconnect")
            self._port_combo.config(state=tk.DISABLED)
            self._log("Connected to " + port)
            self._update_status()
            # Start the serial read loop (it only runs when connected; run() calls it once at startup when _ser is None)
            if self._root and self._root.winfo_exists():
                self._poll_serial()
                self._root.after(400, self._try_robot_idle_mid)
        except Exception as e:
            messagebox.showerror("Connection error", str(e))

    def _disconnect(self):
        self._reading = False
        self._read_buffer = ""
        self._last_heartbeat_time = None
        if self._after_id and self._root:
            try:
                self._root.after_cancel(self._after_id)
            except tk.TclError:
                pass
            self._after_id = None
        if self._ser is not None:
            try:
                self._ser.close()
            except Exception:
                pass
            self._ser = None
        self._connect_btn.config(text="Connect")
        self._port_combo.config(state="normal")
        self._update_status()
        self._log("Disconnected")

    def _send_command(self, cmd):
        """Send command to macropad with newline terminator (firmware expects \\n)."""
        if self._ser is None or not self._ser.is_open:
            return
        try:
            self._ser.write((cmd + "\n").encode("utf-8"))
            self._ser.flush()
            self._log("sent: " + cmd)
        except Exception as e:
            self._log("send error: " + str(e))

    def _poll_serial(self):
        if not self._reading or self._ser is None or not self._ser.is_open:
            return
        try:
            data = self._ser.read(self._ser.in_waiting or 1)
            if data:
                text = data.decode("utf-8", errors="replace")
                self._read_queue.put(text)
        except Exception:
            pass
        if self._root and self._root.winfo_exists():
            self._after_id = self._root.after(50, self._poll_serial)

    def _drain_serial(self):
        while True:
            try:
                text = self._read_queue.get_nowait()
                self._read_buffer += text
            except queue.Empty:
                break
        parts = self._read_buffer.replace("\r", "\n").split("\n")
        self._read_buffer = parts.pop()
        for raw_line in parts:
            line = raw_line.strip()
            if not line:
                continue
            if line == "hb99":
                self._last_heartbeat_time = time.monotonic()
                continue
            self._log("recv: " + line)
            self._handle_key(line)
        token = self._read_buffer.strip()
        if token == "hb99":
            self._last_heartbeat_time = time.monotonic()
            self._read_buffer = ""
        elif token in KEY_TO_CELL:
            self._log("recv: " + token)
            self._handle_key(token)
            self._read_buffer = ""

    def _handle_key(self, text):
        """Process kp03..kp11 from macropad as cell selection."""
        if self._game_over or self._ser is None or not self._ser.is_open:
            return
        # Do not accept any new moves while the robot is still executing pose commands.
        if self._robot_is_busy():
            return
        for token in text.split():
            token = token.strip()
            cell = KEY_TO_CELL.get(token)
            if cell is None or self._board[cell] is not None:
                continue
            mode = self._game_mode_idx
            if mode == 1:  # 2 Player: any turn from macropad
                moved_side = self._turn
                self._place(cell, moved_side)
                self._check_game_over()
                if not self._game_over:
                    next_turn = 'O' if moved_side == 'X' else 'X'
                    # If the robot started moving, delay enabling the next player's turn.
                    if self._robot_move_pick is not None:
                        self._pending_turn_value = next_turn
                        self._pending_turn_command = "rtrn" if next_turn == 'X' else "btrn"
                    else:
                        self._turn = next_turn
                        self._send_command("rtrn" if self._turn == 'X' else "btrn")
                self._update_status()
                return
            if mode == 0:  # 1 Player: only human (X) from macropad
                if self._turn != 'X':
                    continue
                self._place(cell, 'X')
                self._turn = 'O'
                self._send_command("btrn")
                self._check_game_over()
                if not self._game_over and self._root:
                    self._root.after(400, self._do_computer_move)
                return
            # mode 2 CvC: ignore macropad key for moves (computer only)
            # fallthrough: place anyway for 2P already handled

    def _place(self, cell, side):
        """Place side ('X' or 'O') in cell and update macropad. Update piece location (home -> board T00-T08).
        Robot: move piece from corresponding red/blue home waypoint to board cell T00-T08."""
        # Prevent concurrent placements while the robot is still moving the previous piece.
        if self._robot_is_busy():
            self._log("Robot busy (move in progress), ignoring place for cell %d" % cell)
            return
        board_waypoint = "T%02d" % cell  # cell 0-8 -> T00-T08
        pick_waypoint = None
        if side == 'X':
            for i in range(5):
                if self._red_piece_locations[i].startswith("R"):
                    pick_waypoint = self._red_piece_locations[i]
                    self._red_piece_locations[i] = board_waypoint
                    break
        else:
            for i in range(5):
                if self._blue_piece_locations[i].startswith("B"):
                    pick_waypoint = self._blue_piece_locations[i]
                    self._blue_piece_locations[i] = board_waypoint
                    break
        self._board[cell] = side
        cmd = ("sr" if side == 'X' else "sb") + f"{cell:02d}"
        self._send_command(cmd)
        self._update_piece_locations_display()
        # Robot: pick from red/blue home, place on board (pick -> grab -> place -> release).
        # Wait for current move to finish before starting another (each step waits for result before next).
        if (pick_waypoint and board_waypoint in self._waypoints and pick_waypoint in self._waypoints
                and 'MID' in self._waypoints):
            if self._robot_move_pick is not None:
                self._log("Robot busy (move in progress), skipping place for cell %d" % cell)
                return
            self._robot_move_pick = pick_waypoint
            self._robot_move_place = board_waypoint
            self._robot_move_step = 0
            self._robot_sequence_busy = True
            self._log("Robot: place %s -> %s (piece from %s to cell %d)" % (
                pick_waypoint, board_waypoint, pick_waypoint, cell))
            self._robot_place_piece_step()

    def _check_game_over(self):
        self._winner = check_winner(self._board)
        if self._winner:
            self._game_over = True
            if self._winner == 'X':
                self._send_command("rwin")
            elif self._winner == 'O':
                self._send_command("bwin")
            self._update_status()
            return True
        return False

    def _do_computer_move(self):
        self._pending_computer_move_id = None
        if self._game_over or self._ser is None or not self._ser.is_open:
            return
        # Wait for robot to finish before placing another piece.
        if self._robot_is_busy():
            if self._root:
                self._pending_computer_move_id = self._root.after(200, self._do_computer_move)
            return
        empty = empty_cells(self._board)
        if not empty:
            return
        cell = best_move(self._board, self._turn)
        if cell is None:
            cell = random.choice(empty)
        self._place(cell, self._turn)
        if self._check_game_over():
            return
        self._turn = 'O' if self._turn == 'X' else 'X'
        self._send_command("rtrn" if self._turn == 'X' else "btrn")
        self._update_status()
        # CvC: schedule next computer move
        if self._game_mode_idx == 2 and not self._game_over and self._root:
            self._pending_computer_move_id = self._root.after(600, self._do_computer_move)

    def _do_logical_reset(self):
        """Clear game state, piece locations, send clrb/rtrn; robot to MID (or HOME if no MID)."""
        self._board = [None] * 9
        self._turn = 'X'
        self._game_over = False
        self._winner = None
        self._game_mode_idx = self._mode_combo.current()
        self._red_piece_locations = ["R00", "R01", "R02", "R03", "R04"]
        self._blue_piece_locations = ["B00", "B01", "B02", "B03", "B04"]
        self._update_piece_locations_display()
        if self._ser is not None and self._ser.is_open:
            self._send_command("clrb")
            self._send_command("rtrn")
        if 'MID' in self._waypoints:
            self._robot_go_mid()
        else:
            self._robot_go_home()
        self._update_status()
        self._manual_xyz_realtime_enabled = True
        self._update_manual_xyz_realtime(force=True)
        self._log("Game reset. Mode: " + self.GAME_MODES[self._game_mode_idx])
        if self._game_mode_idx == 2 and self._root:
            self._pending_computer_move_id = self._root.after(500, self._do_computer_move)

    def _on_reset(self):
        if self._pending_computer_move_id and self._root:
            try:
                self._root.after_cancel(self._pending_computer_move_id)
            except tk.TclError:
                pass
            self._pending_computer_move_id = None
        self._pending_turn_value = None
        self._pending_turn_command = None
        # Build queue of (from_waypoint, to_waypoint) for pieces currently on the board
        return_queue = []
        for i in range(5):
            loc = self._red_piece_locations[i]
            if loc.startswith("T"):
                return_queue.append((loc, "R%02d" % i))
        for i in range(5):
            loc = self._blue_piece_locations[i]
            if loc.startswith("T"):
                return_queue.append((loc, "B%02d" % i))
        if not return_queue:
            # No pieces on board: just logical reset and go home
            self._robot_move_pick = None
            self._robot_move_place = None
            self._robot_move_step = 0
            self._robot_sequence_busy = False
            self._pose_goal_in_flight = False
            self._em_goal_in_flight = False
            self._reset_return_queue = None
            self._do_logical_reset()
            return
        # Cancel any in-progress robot move so we can start return sequence
        self._robot_move_pick = None
        self._robot_move_place = None
        self._robot_move_step = 0
        self._robot_sequence_busy = False
        self._pose_goal_in_flight = False
        self._em_goal_in_flight = False
        self._reset_return_queue = return_queue
        self._log("Reset: returning %d piece(s) to home slots." % len(return_queue))
        # Start first return: pick from board, place at home
        from_wp, to_wp = self._reset_return_queue.pop(0)
        self._robot_move_pick = from_wp
        self._robot_move_place = to_wp
        self._robot_move_step = 0
        self._robot_sequence_busy = True
        self._log("Robot: reset - returning %s -> %s" % (from_wp, to_wp))
        self._robot_place_piece_step()

    def _on_close(self):
        # Stop realtime manual XYZ updates
        self._manual_xyz_realtime_enabled = False
        if getattr(self, '_manual_xyz_after_id', None) and self._root:
            try:
                self._root.after_cancel(self._manual_xyz_after_id)
            except tk.TclError:
                pass

        if self._pending_computer_move_id and self._root:
            try:
                self._root.after_cancel(self._pending_computer_move_id)
            except tk.TclError:
                pass
        self._disconnect()
        if self._root:
            self._root.destroy()
        self._root = None

    def _tick(self):
        self._drain_serial()
        self._update_status()
        if self._root and self._root.winfo_exists():
            self._root.after(80, self._tick)

    def run(self):
        self._build_gui()
        self._poll_serial()
        self._tick()
        while self._root and self._root.winfo_exists():
            rclpy.spin_once(self, timeout_sec=0.05)
            try:
                self._root.update()
            except tk.TclError:
                break
        self._on_close()


def main(args=None):
    rclpy.init(args=args)
    node = MacropadTictactoeNode()
    try:
        node.run()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
