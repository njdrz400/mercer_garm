#!/usr/bin/env python3
"""
GUI interface for the pose list commander: start sequence, monitor position in list,
and be notified when the robot is back at start.
"""

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Int32, Bool, Float64
from std_srvs.srv import Trigger
import tkinter as tk
from tkinter import ttk, messagebox, font as tkfont


class PoseListCommanderInterface(Node):
    """ROS2 node that runs a minimal GUI and subscribes to pose_list_commander status."""

    def __init__(self):
        super().__init__('pose_list_commander_interface')
        self._state = 'idle'
        self._current_index = 0
        self._total_count = 0
        self._back_at_start = False
        self._current_waypoint_name = ''
        self._led_color = 'g'  # g, y, or r from config
        self._pause_duration_sec = 0.0  # current pause duration when pausing

        self._state_sub = self.create_subscription(
            String, 'pose_list_commander/state', self._on_state, 10
        )
        self._current_sub = self.create_subscription(
            Int32, 'pose_list_commander/current_index', self._on_current_index, 10
        )
        self._total_sub = self.create_subscription(
            Int32, 'pose_list_commander/total_count', self._on_total_count, 10
        )
        self._back_sub = self.create_subscription(
            Bool, 'pose_list_commander/back_at_start', self._on_back_at_start, 10
        )
        self._waypoint_name_sub = self.create_subscription(
            String, 'pose_list_commander/current_waypoint_name', self._on_waypoint_name, 10
        )
        self._led_color_sub = self.create_subscription(
            String, 'pose_list_commander/led_color', self._on_led_color, 10
        )
        self._pause_duration_sub = self.create_subscription(
            Float64, 'pose_list_commander/pause_duration_sec', self._on_pause_duration, 10
        )
        self._start_client = self.create_client(Trigger, 'pose_list_commander/start')
        self._cancel_client = self.create_client(Trigger, 'pose_list_commander/cancel')

        self._root = None
        self._status_var = None
        self._progress_var = None
        self._back_at_start_var = None
        self._back_at_start_label = None
        self._start_btn = None
        self._cancel_btn = None
        self._timer_id = None
        self._pending_start_future = None
        self._waypoint_name_var = None
        self._led_canvas = None
        self._led_circle_id = None

    def _on_state(self, msg):
        self._state = msg.data

    def _on_current_index(self, msg):
        self._current_index = msg.data

    def _on_total_count(self, msg):
        self._total_count = msg.data

    def _on_back_at_start(self, msg):
        self._back_at_start = msg.data

    def _on_waypoint_name(self, msg):
        self._current_waypoint_name = msg.data or ''

    def _on_led_color(self, msg):
        c = (msg.data or 'g').strip().lower()
        if c in ('g', 'y', 'r', 'green', 'yellow', 'red'):
            self._led_color = c

    def _on_pause_duration(self, msg):
        self._pause_duration_sec = max(0.0, float(msg.data))

    def _update_gui(self):
        if self._root is None or not self._root.winfo_exists():
            return
        try:
            if self._total_count > 0:
                self._progress_var.set('Position %d of %d' % (self._current_index, self._total_count))
            else:
                self._progress_var.set('—')
            self._waypoint_name_var.set(self._current_waypoint_name or '—')

            # Update LED color (g, y, r or green, yellow, red)
            led_hex = {'g': '#00cc00', 'y': '#e6b800', 'r': '#cc0000',
                       'green': '#00cc00', 'yellow': '#e6b800', 'red': '#cc0000'}.get(
                self._led_color, '#00cc00'
            )
            if self._led_canvas and self._led_circle_id is not None:
                try:
                    self._led_canvas.itemconfig(self._led_circle_id, fill=led_hex, outline=led_hex)
                except tk.TclError:
                    pass

            state_display = {
                'idle': 'Idle',
                'moving': 'Moving to waypoint',
                'pausing': 'Pausing (%.1fs)' % self._pause_duration_sec,
                'returning': 'Returning to start',
                'back_at_start': 'Back at start',
                'cancelled': 'Cancelled',
                'error': 'Error',
            }.get(self._state, self._state)
            self._status_var.set(state_display)

            if self._back_at_start or self._state == 'back_at_start':
                self._back_at_start_var.set('Robot is back at start position.')
                if self._back_at_start_label:
                    self._back_at_start_label.config(foreground='green')
                if self._start_btn:
                    self._start_btn.config(state=tk.NORMAL)
                if self._cancel_btn:
                    self._cancel_btn.config(state=tk.DISABLED)
            else:
                self._back_at_start_var.set('')
                if self._back_at_start_label:
                    self._back_at_start_label.config(foreground='gray')
                if self._state in ('moving', 'returning', 'pausing'):
                    if self._start_btn:
                        self._start_btn.config(state=tk.DISABLED)
                    if self._cancel_btn:
                        self._cancel_btn.config(state=tk.NORMAL)
                else:
                    if self._start_btn:
                        self._start_btn.config(state=tk.NORMAL)
                    if self._cancel_btn:
                        self._cancel_btn.config(state=tk.DISABLED)
        except tk.TclError:
            pass
        # Check pending start result (non-blocking)
        if self._pending_start_future is not None and self._pending_start_future.done():
            try:
                result = self._pending_start_future.result()
                if not result.success:
                    self._root.after(0, lambda: messagebox.showerror('Start failed', result.message or 'Start failed.'))
            except Exception as e:
                self._root.after(0, lambda: messagebox.showerror('Error', str(e)))
            self._pending_start_future = None
        self._timer_id = self._root.after(200, self._update_gui)

    def _start(self):
        if not self._start_client.wait_for_service(timeout_sec=2.0):
            messagebox.showerror('Error', 'pose_list_commander/start service not available.')
            return
        self._pending_start_future = self._start_client.call_async(Trigger.Request())

    def _cancel(self):
        if not self._cancel_client.wait_for_service(timeout_sec=2.0):
            messagebox.showerror('Error', 'pose_list_commander/cancel service not available.')
            return
        self._cancel_client.call_async(Trigger.Request())

    def _create_gui(self):
        self._root = tk.Tk()
        self._root.title('Pose List Commander')
        self._root.geometry('420x340')
        self._root.protocol('WM_DELETE_WINDOW', self._on_close)

        main = ttk.Frame(self._root, padding=12)
        main.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        self._root.columnconfigure(0, weight=1)
        self._root.rowconfigure(0, weight=1)
        main.columnconfigure(1, weight=1)

        ttk.Label(main, text='Pose List Commander', font=('Arial', 14, 'bold')).grid(
            row=0, column=0, columnspan=3, pady=(0, 12)
        )

        ttk.Label(main, text='Status:').grid(row=1, column=0, sticky=tk.W, pady=4)
        self._status_var = tk.StringVar(value='Idle')
        ttk.Label(main, textvariable=self._status_var, font=('Arial', 11)).grid(
            row=1, column=1, sticky=tk.W, pady=4
        )

        ttk.Label(main, text='Progress:').grid(row=2, column=0, sticky=tk.W, pady=4)
        self._progress_var = tk.StringVar(value='—')
        ttk.Label(main, textvariable=self._progress_var).grid(row=2, column=1, sticky=tk.W, pady=4)

        ttk.Label(main, text='Waypoint:').grid(row=3, column=0, sticky=tk.W, pady=4)
        self._waypoint_name_var = tk.StringVar(value='—')
        ttk.Label(main, textvariable=self._waypoint_name_var, font=('Arial', 10)).grid(
            row=3, column=1, sticky=tk.W, pady=4
        )

        # LED indicator (color from config: green, yellow, red)
        led_frame = ttk.Frame(main)
        led_frame.grid(row=4, column=0, columnspan=2, sticky=tk.W, pady=4)
        ttk.Label(led_frame, text='LED:').pack(side=tk.LEFT, padx=(0, 6))
        self._led_canvas = tk.Canvas(led_frame, width=24, height=24, highlightthickness=0)
        self._led_canvas.pack(side=tk.LEFT)
        led_hex = {'g': '#00cc00', 'y': '#e6b800', 'r': '#cc0000',
                   'green': '#00cc00', 'yellow': '#e6b800', 'red': '#cc0000'}.get(self._led_color, '#00cc00')
        self._led_circle_id = self._led_canvas.create_oval(2, 2, 22, 22, fill=led_hex, outline=led_hex)

        ttk.Separator(main, orient=tk.HORIZONTAL).grid(
            row=5, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=12
        )

        self._back_at_start_var = tk.StringVar(value='')
        self._back_at_start_label = ttk.Label(
            main, textvariable=self._back_at_start_var,
            font=tkfont.Font(weight='bold', size=11)
        )
        self._back_at_start_label.grid(row=6, column=0, columnspan=3, pady=8)

        btn_frame = ttk.Frame(main)
        btn_frame.grid(row=7, column=0, columnspan=3, pady=12)
        self._start_btn = ttk.Button(btn_frame, text='Start', command=self._start)
        self._start_btn.pack(side=tk.LEFT, padx=4)
        self._cancel_btn = ttk.Button(btn_frame, text='Cancel', command=self._cancel, state=tk.DISABLED)
        self._cancel_btn.pack(side=tk.LEFT, padx=4)

        ttk.Label(main, text='Start: run waypoints then return to start. Cancel: stop sequence. LED from config.',
                  font=('Arial', 9), foreground='gray').grid(
            row=8, column=0, columnspan=3, pady=(4, 0)
        )

        self._update_gui()

    def _on_close(self):
        if self._timer_id and self._root:
            try:
                self._root.after_cancel(self._timer_id)
            except tk.TclError:
                pass
        if self._root:
            self._root.destroy()
        self._root = None

    def run(self):
        self._create_gui()
        while self._root and self._root.winfo_exists():
            rclpy.spin_once(self, timeout_sec=0.05)
            try:
                self._root.update()
            except tk.TclError:
                break
        self._on_close()


def main():
    rclpy.init()
    node = PoseListCommanderInterface()
    try:
        node.run()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
