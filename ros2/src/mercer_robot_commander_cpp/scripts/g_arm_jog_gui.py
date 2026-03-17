#!/usr/bin/env python3
"""
Python GUI node for jogging the g-arm robot on xyz axis
and controlling the electromagnet.
"""

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from geometry_msgs.msg import PoseStamped, Point, Quaternion
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from g_arm_msgs.action import GoToPose
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox

class GArmJogGUI(Node):
    def __init__(self):
        super().__init__('g_arm_jog_gui')
        
        # TF listener for getting current end effector pose
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.end_effector_frame = 'end_effector_tip'  # Adjust if needed
        self.base_frame = 'base_link'
        
        # Action clients
        self.go_to_pose_client = ActionClient(self, GoToPose, '/go_to_pose')
        self.tool_action_client = ActionClient(
            self,
            FollowJointTrajectory,
            '/tool_controller/follow_joint_trajectory'
        )
        self.magnet_action_client = ActionClient(
            self,
            FollowJointTrajectory,
            '/magnet_controller/follow_joint_trajectory'
        )
        
        # Jog parameters
        self.jog_step = 0.01  # meters per jog command
        self.current_goal_handle = None  # Track current action goal
        
        # Current pose tracking
        self.current_pose = None
        self.current_pose_lock = False  # Prevent multiple simultaneous goals
        
        
        # Electromagnet state
        self.electromagnet_on = False
        
        # Flag to track if GUI is ready
        self.gui_ready = False
        
        self.get_logger().info('GArm Jog GUI node started')
    
    def _create_gui(self):
        """Create and run the GUI"""
        self.root = tk.Tk()
        self.root.title("G-Arm Jog Control")
        self.root.geometry("500x800")
        
        # Main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        
        # Title
        title_label = ttk.Label(main_frame, text="G-Arm Jog Control", font=("Arial", 16, "bold"))
        title_label.grid(row=0, column=0, columnspan=3, pady=10)
        
        # Jog step size
        ttk.Label(main_frame, text="Jog Step (m):").grid(row=1, column=0, sticky=tk.W, pady=5)
        self.step_var = tk.DoubleVar(value=self.jog_step)
        step_spinbox = ttk.Spinbox(main_frame, from_=0.001, to=0.1, increment=0.001, 
                                   textvariable=self.step_var, width=10)
        step_spinbox.grid(row=1, column=1, sticky=tk.W, pady=5)
        
        # Separator
        ttk.Separator(main_frame, orient=tk.HORIZONTAL).grid(row=2, column=0, columnspan=3, 
                                                             sticky=(tk.W, tk.E), pady=10)
        
        # Current position display (read-only labels)
        ttk.Label(main_frame, text="Current Position (m)", font=("Arial", 12, "bold")).grid(
            row=3, column=0, columnspan=3, pady=5
        )
        
        # X current position
        ttk.Label(main_frame, text="X:").grid(row=4, column=0, sticky=tk.W, pady=5)
        self.x_current_var = tk.StringVar(value="0.000")
        x_current_label = ttk.Label(main_frame, textvariable=self.x_current_var, width=12, 
                                   relief=tk.SUNKEN, anchor=tk.W)
        x_current_label.grid(row=4, column=1, sticky=tk.W, pady=5)
        
        # Y current position
        ttk.Label(main_frame, text="Y:").grid(row=5, column=0, sticky=tk.W, pady=5)
        self.y_current_var = tk.StringVar(value="0.000")
        y_current_label = ttk.Label(main_frame, textvariable=self.y_current_var, width=12,
                                   relief=tk.SUNKEN, anchor=tk.W)
        y_current_label.grid(row=5, column=1, sticky=tk.W, pady=5)
        
        # Z current position
        ttk.Label(main_frame, text="Z:").grid(row=6, column=0, sticky=tk.W, pady=5)
        self.z_current_var = tk.StringVar(value="0.000")
        z_current_label = ttk.Label(main_frame, textvariable=self.z_current_var, width=12,
                                   relief=tk.SUNKEN, anchor=tk.W)
        z_current_label.grid(row=6, column=1, sticky=tk.W, pady=5)
        
        # Separator
        ttk.Separator(main_frame, orient=tk.HORIZONTAL).grid(row=7, column=0, columnspan=3, 
                                                             sticky=(tk.W, tk.E), pady=10)
        
        # Target position input
        ttk.Label(main_frame, text="Target Position (m)", font=("Arial", 12, "bold")).grid(
            row=8, column=0, columnspan=3, pady=5
        )
        
        # X target position input
        ttk.Label(main_frame, text="X:").grid(row=9, column=0, sticky=tk.W, pady=5)
        self.x_var = tk.StringVar(value="0.000")
        self.x_entry = ttk.Entry(main_frame, textvariable=self.x_var, width=12)
        self.x_entry.grid(row=9, column=1, sticky=tk.W, pady=5)
        # Allow negative numbers
        self.x_entry.config(validate='key', validatecommand=(self.x_entry.register(self._validate_number), '%P'))
        
        # Y target position input
        ttk.Label(main_frame, text="Y:").grid(row=10, column=0, sticky=tk.W, pady=5)
        self.y_var = tk.StringVar(value="0.000")
        self.y_entry = ttk.Entry(main_frame, textvariable=self.y_var, width=12)
        self.y_entry.grid(row=10, column=1, sticky=tk.W, pady=5)
        # Allow negative numbers
        self.y_entry.config(validate='key', validatecommand=(self.y_entry.register(self._validate_number), '%P'))
        
        # Z target position input
        ttk.Label(main_frame, text="Z:").grid(row=11, column=0, sticky=tk.W, pady=5)
        self.z_var = tk.StringVar(value="0.000")
        self.z_entry = ttk.Entry(main_frame, textvariable=self.z_var, width=12)
        self.z_entry.grid(row=11, column=1, sticky=tk.W, pady=5)
        # Allow negative numbers
        self.z_entry.config(validate='key', validatecommand=(self.z_entry.register(self._validate_number), '%P'))
        
        # Move Robot button
        move_btn = ttk.Button(main_frame, text="Move Robot", command=self._move_to_position)
        move_btn.grid(row=12, column=0, columnspan=3, pady=10)
        
        # Separator
        ttk.Separator(main_frame, orient=tk.HORIZONTAL).grid(row=13, column=0, columnspan=3, 
                                                             sticky=(tk.W, tk.E), pady=10)
        
        # XYZ Jogging controls
        ttk.Label(main_frame, text="XYZ Jogging", font=("Arial", 12, "bold")).grid(
            row=14, column=0, columnspan=3, pady=5
        )
        
        # X axis jog
        ttk.Label(main_frame, text="X Jog:").grid(row=15, column=0, sticky=tk.W, pady=5)
        x_frame = ttk.Frame(main_frame)
        x_frame.grid(row=15, column=1, sticky=(tk.W, tk.E), pady=5)
        ttk.Button(x_frame, text="-", width=5, 
                  command=lambda: self._start_jog('x', -1)).pack(side=tk.LEFT, padx=2)
        ttk.Button(x_frame, text="+", width=5, 
                  command=lambda: self._start_jog('x', 1)).pack(side=tk.LEFT, padx=2)
        
        # Y axis jog
        ttk.Label(main_frame, text="Y Jog:").grid(row=16, column=0, sticky=tk.W, pady=5)
        y_frame = ttk.Frame(main_frame)
        y_frame.grid(row=16, column=1, sticky=(tk.W, tk.E), pady=5)
        ttk.Button(y_frame, text="-", width=5, 
                  command=lambda: self._start_jog('y', -1)).pack(side=tk.LEFT, padx=2)
        ttk.Button(y_frame, text="+", width=5, 
                  command=lambda: self._start_jog('y', 1)).pack(side=tk.LEFT, padx=2)
        
        # Z axis jog
        ttk.Label(main_frame, text="Z Jog:").grid(row=17, column=0, sticky=tk.W, pady=5)
        z_frame = ttk.Frame(main_frame)
        z_frame.grid(row=17, column=1, sticky=(tk.W, tk.E), pady=5)
        ttk.Button(z_frame, text="-", width=5, 
                  command=lambda: self._start_jog('z', -1)).pack(side=tk.LEFT, padx=2)
        ttk.Button(z_frame, text="+", width=5, 
                  command=lambda: self._start_jog('z', 1)).pack(side=tk.LEFT, padx=2)
        
        # Stop/Cancel button
        stop_btn = ttk.Button(main_frame, text="CANCEL", command=self._cancel_current_goal)
        stop_btn.grid(row=18, column=0, columnspan=3, pady=5)
        
        # Home button
        home_btn = ttk.Button(main_frame, text="HOME", command=self._go_to_home)
        home_btn.grid(row=19, column=0, columnspan=3, pady=5)
        
        # Separator
        ttk.Separator(main_frame, orient=tk.HORIZONTAL).grid(row=20, column=0, columnspan=3, 
                                                             sticky=(tk.W, tk.E), pady=10)
        
        # Electromagnet control
        ttk.Label(main_frame, text="Electromagnet", font=("Arial", 12, "bold")).grid(
            row=21, column=0, columnspan=3, pady=5
        )
        
        self.magnet_var = tk.BooleanVar(value=False)
        magnet_toggle = ttk.Checkbutton(main_frame, text="Electromagnet ON", 
                                       variable=self.magnet_var,
                                       command=self._toggle_electromagnet)
        magnet_toggle.grid(row=22, column=0, columnspan=3, pady=5)
        
        # Separator
        ttk.Separator(main_frame, orient=tk.HORIZONTAL).grid(row=23, column=0, columnspan=3, 
                                                             sticky=(tk.W, tk.E), pady=10)
        
        # Status label
        self.status_label = ttk.Label(main_frame, text="Ready", foreground="green")
        self.status_label.grid(row=24, column=0, columnspan=3, pady=10)
        
        self.root.focus_set()
        
        # Mark GUI as ready
        self.gui_ready = True
        
        # Start periodic ROS2 spin (non-blocking)
        self._schedule_ros_spin()
        
        # Start GUI main loop (blocks here)
        self.root.mainloop()
    
    def _start_jog(self, axis, direction):
        """Send a jog command using GoToPose action"""
        if self.current_pose_lock:
            self._update_status("Previous command still executing...", "orange")
            return
        
        # Get current pose
        current_pose = self._get_current_pose()
        if current_pose is None:
            self._update_status("Error: Could not get current pose", "red")
            return
        
        # Calculate target pose
        step = self.step_var.get()
        target_pose = PoseStamped()
        target_pose.header.frame_id = current_pose.header.frame_id
        target_pose.header.stamp = self.get_clock().now().to_msg()
        target_pose.pose.position = Point(
            x=current_pose.pose.position.x + (step * direction if axis == 'x' else 0.0),
            y=current_pose.pose.position.y + (step * direction if axis == 'y' else 0.0),
            z=current_pose.pose.position.z + (step * direction if axis == 'z' else 0.0)
        )
        # Keep same orientation
        target_pose.pose.orientation = current_pose.pose.orientation
        
        # Send action goal
        self._send_jog_goal(target_pose, axis, direction)
    
    def _get_current_pose(self):
        """Get current end effector pose from TF"""
        try:
            transform = self.tf_buffer.lookup_transform(
                self.base_frame,
                self.end_effector_frame,
                rclpy.time.Time()
            )
            
            pose = PoseStamped()
            pose.header.frame_id = self.base_frame
            pose.header.stamp = transform.header.stamp
            pose.pose.position.x = transform.transform.translation.x
            pose.pose.position.y = transform.transform.translation.y
            pose.pose.position.z = transform.transform.translation.z
            pose.pose.orientation = transform.transform.rotation
            
            return pose
        except TransformException as ex:
            self.get_logger().warn(f'Could not get current pose: {ex}')
            # Try to use last known pose if available
            if self.current_pose is not None:
                return self.current_pose
            return None
    
    def _send_jog_goal(self, target_pose, axis, direction):
        """Send a GoToPose action goal for jogging"""
        if not self.go_to_pose_client.wait_for_server(timeout_sec=1.0):
            self._update_status("Error: GoToPose action server not available", "red")
            return
        
        # Create goal
        goal_msg = GoToPose.Goal()
        goal_msg.target = target_pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28  # Large tolerance to ignore orientation
        goal_msg.timeout_sec = 5.0
        goal_msg.allow_orientation = True  # Ignore orientation constraints
        goal_msg.electromagnet_on = self.electromagnet_on  # Keep electromagnet state after jog

        self.current_pose_lock = True
        self._update_status(f"Moving {axis.upper()}: {'+' if direction > 0 else '-'} {self.step_var.get():.3f}m...", "blue")
        
        # Send goal asynchronously
        send_goal_future = self.go_to_pose_client.send_goal_async(
            goal_msg,
            feedback_callback=lambda feedback: self._jog_feedback_callback(feedback, axis, direction)
        )
        send_goal_future.add_done_callback(
            lambda future: self._jog_goal_response_callback(future, target_pose, axis, direction)
        )
    
    def _jog_goal_response_callback(self, future, target_pose, axis, direction):
        """Callback for jog goal response"""
        self.current_goal_handle = future.result()
        if not self.current_goal_handle.accepted:
            self._update_status("Jog command rejected", "red")
            self.current_pose_lock = False
            return
        
        # Get result
        result_future = self.current_goal_handle.get_result_async()
        result_future.add_done_callback(
            lambda future: self._jog_result_callback(future, target_pose, axis, direction)
        )
    
    def _jog_feedback_callback(self, feedback_msg, axis, direction):
        """Callback for jog feedback"""
        feedback = feedback_msg.feedback
        # Could update status with progress if desired
        pass
    
    def _jog_result_callback(self, future, target_pose, axis, direction):
        """Callback for jog result"""
        result = future.result().result
        self.current_pose_lock = False
        
        if result.success:
            # Update current pose from result
            self.current_pose = target_pose
            self._update_current_position_labels(target_pose)
            self._update_target_position_text_boxes(target_pose)
            self._update_status(f"Moved {axis.upper()}: {'+' if direction > 0 else '-'} {self.step_var.get():.3f}m", "green")
        else:
            self._update_status(f"Jog failed: {result.message}", "red")
            # Show alert if IK solution not found
            if result.error_code == 3 or "IK solution" in result.message:
                self._show_ik_error_alert(result.message)
    
    def _cancel_current_goal(self):
        """Cancel the current action goal"""
        if self.current_goal_handle is not None:
            self.get_logger().info('Canceling current goal...')
            cancel_future = self.current_goal_handle.cancel_goal_async()
            cancel_future.add_done_callback(self._cancel_done_callback)
        else:
            self._update_status("No active goal to cancel", "orange")
    
    def _cancel_done_callback(self, future):
        """Callback when cancel is complete"""
        cancel_response = future.result()
        if len(cancel_response.goals_canceling) > 0:
            self._update_status("Goal canceled", "orange")
            self.current_pose_lock = False
        else:
            self._update_status("Cancel failed - goal may have already completed", "orange")
    
    def _go_to_home(self):
        """Move robot to home position"""
        if self.current_pose_lock:
            self._update_status("Previous command still executing...", "orange")
            return
        
        if not self.go_to_pose_client.wait_for_server(timeout_sec=1.0):
            self._update_status("Error: GoToPose action server not available", "red")
            return
        
        # Home position: x=0.22, y=0.0, z=0.29 (from SRDF: joint1=0, joint2=0, joint3=0)
        home_pose = PoseStamped()
        home_pose.header.frame_id = 'base_link'
        home_pose.header.stamp = self.get_clock().now().to_msg()
        home_pose.pose.position = Point(x=0.22, y=0.0, z=0.29)
        home_pose.pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
        
        # Create goal
        goal_msg = GoToPose.Goal()
        goal_msg.target = home_pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28  # Large tolerance to ignore orientation
        goal_msg.timeout_sec = 10.0
        goal_msg.allow_orientation = True  # Ignore orientation constraints
        goal_msg.electromagnet_on = self.electromagnet_on  # Keep electromagnet state after home

        self.current_pose_lock = True
        self._update_status("Moving to Home position...", "blue")
        
        # Send goal asynchronously
        send_goal_future = self.go_to_pose_client.send_goal_async(
            goal_msg,
            feedback_callback=self._home_feedback_callback
        )
        send_goal_future.add_done_callback(self._home_goal_response_callback)
    
    def _home_goal_response_callback(self, future):
        """Callback for home goal response"""
        self.current_goal_handle = future.result()
        if not self.current_goal_handle.accepted:
            self._update_status("Home command rejected", "red")
            self.current_pose_lock = False
            return
        
        # Get result
        result_future = self.current_goal_handle.get_result_async()
        result_future.add_done_callback(self._home_result_callback)
    
    def _home_feedback_callback(self, feedback_msg):
        """Callback for home feedback"""
        feedback = feedback_msg.feedback
        # Could update status with progress if desired
        pass
    
    def _home_result_callback(self, future):
        """Callback for home result"""
        result = future.result().result
        self.current_pose_lock = False
        
        if result.success:
            # Update current pose
            home_pose = PoseStamped()
            home_pose.header.frame_id = 'base_link'
            home_pose.pose.position = Point(x=0.22, y=0.0, z=0.29)
            home_pose.pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
            self.current_pose = home_pose
            self._update_current_position_labels(home_pose)
            self._update_target_position_text_boxes(home_pose)
            self._update_status("Successfully moved to Home position", "green")
        else:
            self._update_status(f"Home movement failed: {result.message}", "red")
            # Show alert if IK solution not found
            if result.error_code == 3 or "IK solution" in result.message:
                self._show_ik_error_alert(result.message)
    
    def _move_to_position(self):
        """Move robot to the position specified in the text boxes"""
        if self.current_pose_lock:
            self._update_status("Previous command still executing...", "orange")
            return
        
        try:
            x = float(self.x_var.get())
            y = float(self.y_var.get())
            z = float(self.z_var.get())
        except ValueError:
            self._update_status("Error: Invalid position values. Please enter numbers.", "red")
            return
        
        if not self.go_to_pose_client.wait_for_server(timeout_sec=1.0):
            self._update_status("Error: GoToPose action server not available", "red")
            return
        
        # Create target pose
        target_pose = PoseStamped()
        target_pose.header.frame_id = 'base_link'
        target_pose.header.stamp = self.get_clock().now().to_msg()
        target_pose.pose.position = Point(x=x, y=y, z=z)
        # Keep current orientation or use default
        if self.current_pose is not None:
            target_pose.pose.orientation = self.current_pose.pose.orientation
        else:
            target_pose.pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
        
        # Create goal
        goal_msg = GoToPose.Goal()
        goal_msg.target = target_pose
        goal_msg.pos_tolerance_m = 0.01
        goal_msg.ang_tolerance_rad = 6.28  # Large tolerance to ignore orientation
        goal_msg.timeout_sec = 10.0
        goal_msg.allow_orientation = True  # Ignore orientation constraints
        goal_msg.electromagnet_on = self.electromagnet_on  # Keep electromagnet state after move

        self.current_pose_lock = True
        self._update_status(f"Moving to ({x:.3f}, {y:.3f}, {z:.3f})...", "blue")
        
        # Send goal asynchronously
        send_goal_future = self.go_to_pose_client.send_goal_async(
            goal_msg,
            feedback_callback=self._move_to_position_feedback_callback
        )
        send_goal_future.add_done_callback(
            lambda future: self._move_to_position_goal_response_callback(future, target_pose)
        )
    
    def _move_to_position_goal_response_callback(self, future, target_pose):
        """Callback for move to position goal response"""
        self.current_goal_handle = future.result()
        if not self.current_goal_handle.accepted:
            self._update_status("Move command rejected", "red")
            self.current_pose_lock = False
            return
        
        # Get result
        result_future = self.current_goal_handle.get_result_async()
        result_future.add_done_callback(
            lambda future: self._move_to_position_result_callback(future, target_pose)
        )
    
    def _move_to_position_feedback_callback(self, feedback_msg):
        """Callback for move to position feedback"""
        feedback = feedback_msg.feedback
        # Could update status with progress if desired
        pass
    
    def _move_to_position_result_callback(self, future, target_pose):
        """Callback for move to position result"""
        result = future.result().result
        self.current_pose_lock = False
        
        if result.success:
            self.current_pose = target_pose
            self._update_current_position_labels(target_pose)
            self._update_status("Successfully moved to target position", "green")
        else:
            self._update_status(f"Move failed: {result.message}", "red")
            # Show alert if IK solution not found
            if result.error_code == 3 or "IK solution" in result.message:
                self._show_ik_error_alert(result.message)
    
    def _show_ik_error_alert(self, error_message):
        """Show an alert dialog when IK solution is not found"""
        if hasattr(self, 'root'):
            # Schedule on GUI thread
            self.root.after(0, lambda: messagebox.showerror(
                "IK Solution Not Found",
                f"Inverse Kinematics solution could not be found.\n\n"
                f"Error: {error_message}\n\n"
                f"The target pose may be unreachable or outside the robot's workspace.\n"
                f"Please try a different position."
            ))
    
    def _validate_number(self, value):
        """Validate that the input is a valid number (including negative)"""
        if value == "" or value == "-":
            return True  # Allow empty or just minus sign (user typing)
        try:
            float(value)
            return True
        except ValueError:
            return False
    
    def _update_current_position_labels(self, pose):
        """Update the current position labels with the given pose"""
        if hasattr(self, 'x_current_var') and hasattr(self, 'y_current_var') and hasattr(self, 'z_current_var'):
            self.x_current_var.set(f"{pose.pose.position.x:.3f}")
            self.y_current_var.set(f"{pose.pose.position.y:.3f}")
            self.z_current_var.set(f"{pose.pose.position.z:.3f}")
    
    def _update_target_position_text_boxes(self, pose):
        """Update the target position text boxes with the given pose"""
        if hasattr(self, 'x_var') and hasattr(self, 'y_var') and hasattr(self, 'z_var'):
            self.x_var.set(f"{pose.pose.position.x:.3f}")
            self.y_var.set(f"{pose.pose.position.y:.3f}")
            self.z_var.set(f"{pose.pose.position.z:.3f}")
    
    
    def _toggle_electromagnet(self):
        """Toggle electromagnet on/off"""
        target_state = self.magnet_var.get()
        
        if target_state == self.electromagnet_on:
            return  # Already in desired state
        
        self.electromagnet_on = target_state
        self._control_electromagnet(target_state)
    
    def _control_electromagnet(self, turn_on):
        """Control electromagnet via action client"""
        # Try tool_controller first, then magnet_controller
        action_client = None
        controller_name = ""
        
        if self.tool_action_client.wait_for_server(timeout_sec=0.1):
            action_client = self.tool_action_client
            controller_name = "tool_controller"
        elif self.magnet_action_client.wait_for_server(timeout_sec=0.1):
            action_client = self.magnet_action_client
            controller_name = "magnet_controller"
        
        if not action_client:
            self._update_status("Error: No electromagnet controller available", "red")
            return
        
        # Create trajectory
        trajectory = JointTrajectory()
        trajectory.joint_names = ["jointPWM"]
        
        point = JointTrajectoryPoint()
        point.positions = [1.0 if turn_on else 0.0]
        point.time_from_start = rclpy.duration.Duration(seconds=0.5).to_msg()
        trajectory.points = [point]
        
        # Create goal
        goal = FollowJointTrajectory.Goal()
        goal.trajectory = trajectory
        
        # Send goal asynchronously
        send_goal_future = action_client.send_goal_async(goal)
        send_goal_future.add_done_callback(
            lambda future: self._electromagnet_goal_response_callback(future, turn_on)
        )
        
        self._update_status(f"Turning electromagnet {'ON' if turn_on else 'OFF'}...", "blue")
    
    def _electromagnet_goal_response_callback(self, future, turn_on):
        """Callback for electromagnet goal response"""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self._update_status("Failed to send electromagnet command", "red")
            return
        
        # Get result
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(
            lambda future: self._electromagnet_result_callback(future, turn_on)
        )
    
    def _electromagnet_result_callback(self, future, turn_on):
        """Callback for electromagnet result"""
        result = future.result().result
        if result.error_code == 0:
            self._update_status(f"Electromagnet {'ON' if turn_on else 'OFF'}", "green")
        else:
            self._update_status(f"Electromagnet command failed: {result.error_string}", "red")
    
    def _schedule_ros_spin(self):
        """Schedule periodic ROS2 spinning (non-blocking)"""
        if hasattr(self, 'root'):
            # Spin ROS2 once
            rclpy.spin_once(self, timeout_sec=0.01)
            # Schedule next spin
            self.root.after(10, self._schedule_ros_spin)
    
    def _update_status(self, message, color="black"):
        """Update status label"""
        if hasattr(self, 'status_label') and hasattr(self, 'root'):
            self.status_label.config(text=message, foreground=color)


def main(args=None):
    rclpy.init(args=args)
    
    node = GArmJogGUI()
    
    # Create GUI (this will block in mainloop)
    node._create_gui()
    
    # Cleanup after GUI closes
    try:
        node.destroy_node()
        rclpy.shutdown()
    except:
        pass


if __name__ == '__main__':
    main()
