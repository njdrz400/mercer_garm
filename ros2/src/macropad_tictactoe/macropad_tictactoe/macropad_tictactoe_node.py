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
from tkinter import ttk, messagebox, scrolledtext

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from geometry_msgs.msg import PoseStamped, Point, Quaternion
from g_arm_msgs.action import GoToPose
from ament_index_python.packages import get_package_share_directory

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
        self._robot_move_pick = None   # waypoint name (R0x or B0x) while move in progress
        self._robot_move_place = None  # waypoint name (T0x)
        self._robot_move_step = 0      # 0=go pick mag off, 1=grab, 2=go place, 3=release

        self._root = None
        self._status_var = None
        self._port_combo = None
        self._connect_btn = None
        self._mode_combo = None
        self._reset_btn = None
        self._log_text = None

    def _load_waypoints(self):
        """Load waypoints from config/waypoints.yaml (used to guide robot arm)."""
        if yaml is None:
            self.get_logger().warn("python3-yaml not available; waypoints not loaded")
            return
        path = None
        try:
            pkg_share = get_package_share_directory('macropad_tictactoe')
            path = os.path.join(pkg_share, 'config', 'waypoints.yaml')
        except Exception:
            pass
        if not path or not os.path.isfile(path):
            # Fallback: config next to package (e.g. when running from source)
            this_dir = os.path.dirname(os.path.abspath(__file__))
            path = os.path.join(os.path.dirname(this_dir), 'config', 'waypoints.yaml')
        try:
            if os.path.isfile(path):
                with open(path, 'r') as f:
                    data = yaml.safe_load(f)
                self._waypoints = data.get('waypoints', {})
                self.get_logger().info(
                    "Loaded %d waypoints from config/waypoints.yaml" % len(self._waypoints)
                )
            else:
                self.get_logger().warn("waypoints.yaml not found at %s" % path)
                self._waypoints = {}
        except Exception as e:
            self.get_logger().warn("Could not load waypoints: %s" % e)
            self._waypoints = {}

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

    def _robot_place_piece_step(self):
        """Send one step of pick->grab->place->release. Steps 0–3; called from _place or result callback."""
        if self._robot_move_pick is None or self._robot_move_place is None:
            return
        step = self._robot_move_step
        if step == 0:
            wp_name = self._robot_move_pick
            magnet_on = False
        elif step == 1:
            wp_name = self._robot_move_pick
            magnet_on = True
        elif step == 2:
            wp_name = self._robot_move_place
            magnet_on = True
        else:
            wp_name = self._robot_move_place
            magnet_on = False
        pose = self._waypoint_pose(wp_name)
        if not pose:
            self.get_logger().warn("Robot move: waypoint '%s' not found" % wp_name)
            self._robot_move_pick = self._robot_move_place = None
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().warn("Robot move: go_to_pose server not available")
            self._robot_move_pick = self._robot_move_place = None
            return
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = magnet_on
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._robot_place_goal_response_callback)

    def _robot_place_goal_response_callback(self, future):
        """Handle send_goal_async result; on accept, wait for result and then advance step."""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot place: goal rejected")
            self._robot_move_pick = self._robot_move_place = None
            return
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._robot_place_result_callback)

    def _robot_place_result_callback(self, future):
        """After each step: advance or finish. Next step is scheduled from executor context."""
        result = future.result().result
        if not result.success:
            self.get_logger().warn("Robot place step failed: %s" % getattr(result, 'message', ''))
            self._robot_move_pick = self._robot_move_place = None
            return
        self._robot_move_step += 1
        if self._robot_move_step >= 4:
            self._robot_move_pick = self._robot_move_place = None
            self._robot_move_step = 0
            self.get_logger().info("Robot placed piece.")
            return
        self._robot_place_piece_step()

    def _robot_go_home(self):
        """Send robot to HOME waypoint (non-blocking). Called on game reset."""
        pose = self._waypoint_pose('HOME')
        if not pose:
            self.get_logger().warn("Robot go home: HOME waypoint not found")
            return
        if not self._go_to_pose_client.wait_for_server(timeout_sec=0.5):
            self.get_logger().warn("Robot go home: go_to_pose server not available")
            return
        goal_msg = GoToPose.Goal()
        goal_msg.target = pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28
        goal_msg.timeout_sec = 15.0
        goal_msg.allow_orientation = True
        goal_msg.electromagnet_on = False
        send_future = self._go_to_pose_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self._robot_go_home_response_callback)

    def _robot_go_home_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn("Robot go home: goal rejected")
            return
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._robot_go_home_result_callback)

    def _robot_go_home_result_callback(self, future):
        result = future.result().result
        if result.success:
            self.get_logger().info("Robot at HOME.")
        else:
            self.get_logger().warn("Robot go home failed: %s" % getattr(result, 'message', ''))

    def _build_gui(self):
        self._root = tk.Tk()
        self._root.title("Macropad Tic-Tac-Toe")
        self._root.geometry("520x380")
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
            self._port_combo.set("/dev/ttyACM0" if __import__("sys").platform != "win32" else "COM1")
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

        # Log
        ttk.Label(main, text="Log:").pack(anchor=tk.W)
        self._log_text = scrolledtext.ScrolledText(main, height=8, font=("Consolas", 9), state=tk.DISABLED)
        self._log_text.pack(fill=tk.BOTH, expand=True, pady=(2, 0))

        self._root.protocol("WM_DELETE_WINDOW", self._on_close)
        self._log_waypoints()

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
        for token in text.split():
            token = token.strip()
            cell = KEY_TO_CELL.get(token)
            if cell is None or self._board[cell] is not None:
                continue
            mode = self._game_mode_idx
            if mode == 1:  # 2 Player: any turn from macropad
                self._place(cell, self._turn)
                self._check_game_over()
                if not self._game_over:
                    self._turn = 'O' if self._turn == 'X' else 'X'
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
        # Robot: pick from red/blue home, place on board (pick -> grab -> place -> release)
        if pick_waypoint and board_waypoint in self._waypoints and pick_waypoint in self._waypoints:
            self._robot_move_pick = pick_waypoint
            self._robot_move_place = board_waypoint
            self._robot_move_step = 0
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

    def _on_reset(self):
        if self._pending_computer_move_id and self._root:
            try:
                self._root.after_cancel(self._pending_computer_move_id)
            except tk.TclError:
                pass
            self._pending_computer_move_id = None
        # Cancel any in-progress robot place sequence
        self._robot_move_pick = None
        self._robot_move_place = None
        self._robot_move_step = 0
        self._board = [None] * 9
        self._turn = 'X'
        self._game_over = False
        self._winner = None
        self._game_mode_idx = self._mode_combo.current()
        # Reset piece locations to home: red at R00-R04, blue at B00-B04
        self._red_piece_locations = ["R00", "R01", "R02", "R03", "R04"]
        self._blue_piece_locations = ["B00", "B01", "B02", "B03", "B04"]
        if self._ser is not None and self._ser.is_open:
            self._send_command("clrb")
            self._send_command("rtrn")
        # Robot: move arm back to HOME waypoint
        self._robot_go_home()
        self._update_status()
        self._log("Game reset. Mode: " + self.GAME_MODES[self._game_mode_idx])
        if self._game_mode_idx == 2 and self._root:
            self._pending_computer_move_id = self._root.after(500, self._do_computer_move)

    def _on_close(self):
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
