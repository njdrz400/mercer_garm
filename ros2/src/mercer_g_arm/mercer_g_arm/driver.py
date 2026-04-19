import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
from std_srvs.srv import Trigger

import math, threading, time
from termcolor import colored
from mercer_g_arm.mercer_g_arm_lib import robot

class Driver(Node):
    
    __goal_joints_state = dict()
    __received_joint_states = False
    
    def __init__(self):
        super().__init__('g_arm_driver')
        self.declare_parameter('usb_port', '/dev/ttyUSB0')
        self.declare_parameter('X_ZERO_REAL_ANGLE', 135)
        usb_port = self.get_parameter('usb_port').value
        x_zero_real_angle = float(self.get_parameter('X_ZERO_REAL_ANGLE').value)

        self.subscription = self.create_subscription(JointState, 'joint_commands', self.joints_state_callback, 10)
        
        self.robot = robot.Robot(x_zero_real_angle=x_zero_real_angle)
        
        self.get_logger().info("Connecting and calibrating the robot (May take a while)")
        
        if not self.robot.start(port=usb_port):
            self.get_logger().error(
                f"Unable to start communications on {usb_port}. "
                f"Do you have permissions? (Try: sudo chmod 666 {usb_port})"
            )
            exit(1)

        # When False, do not stream G-code from joint_commands; otherwise every
        # setAngles (G01) re-engages steppers and masks GRBL $1=0 idle disable.
        self._motors_enabled = True
        self._motor_cmd_lock = threading.Lock()
        # Last angles actually sent to GRBL (deg); avoids flooding the planner with
        # identical G01 lines at 10 Hz, which keeps status != Idle and blocks $1=0.
        self._last_sent_cmd_deg = None
        self._angle_resend_epsilon_deg = 0.05
            
        self.get_logger().info(colored("Robot is ready to move!", "green"))
        
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.joints_state_apply)
        self.js_pub = self.create_publisher(JointState, 'joint_states', 10)

        self.srv_enable_motors = self.create_service(
            Trigger,
            'g_arm_driver/enable_motors',
            self.enable_motors_callback,
        )
        self.srv_disable_motors = self.create_service(
            Trigger,
            'g_arm_driver/disable_motors',
            self.disable_motors_callback,
        )


    # Callback of /joint_states. This stores the joints positions in memory      
    def joints_state_callback(self, msg):
        self.__received_joint_states = True
        
        n_joints = len(msg.name)
        
        for i in range(n_joints):
            
            joint_name = msg.name[i]
            joint_position = msg.position[i]
            
            self.__goal_joints_state[joint_name] = joint_position

    # Apply the stored joints values        
    def joints_state_apply(self):
        
        if self.__received_joint_states:
            
            j1 = math.degrees(self.__goal_joints_state["joint1"])
            j2 = math.degrees(self.__goal_joints_state["joint2"])
            j3 = math.degrees(self.__goal_joints_state["joint3"])
            
            # Set PWM value, default to zero if jointPWM doesn't exist
            if "jointPWM" in self.__goal_joints_state:
                pwm = self.__goal_joints_state["jointPWM"]
            else:
                pwm = 0.0
                self.get_logger().warn("jointPWM key is missing in joint state message, setting PWM to zero")

            with self._motor_cmd_lock:
                if not self._motors_enabled:
                    pass
                else:
                    self.robot.toolPWM(pwm)
                    last = self._last_sent_cmd_deg
                    moved = last is None or (
                        abs(j1 - last[0]) > self._angle_resend_epsilon_deg
                        or abs(j2 - last[1]) > self._angle_resend_epsilon_deg
                        or abs(j3 - last[2]) > self._angle_resend_epsilon_deg
                    )
                    if moved:
                        self.robot.setAngles(j1, j2, j3)
                        self._last_sent_cmd_deg = (j1, j2, j3)
            
            msg = JointState()
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.name = ["joint1","joint2","joint3","jointPWM"]
            msg.position = [
                self.__goal_joints_state["joint1"],
                self.__goal_joints_state["joint2"],
                self.__goal_joints_state["joint3"],
                self.__goal_joints_state.get("jointPWM", 0.0),
            ]
            self.js_pub.publish(msg)

    def enable_motors_callback(self, request, response):
        try:
            with self._motor_cmd_lock:
                self.robot.enableAllMotors()
                self._motors_enabled = True
                self._last_sent_cmd_deg = None
        except Exception as ex:
            self.get_logger().error(f'enable_motors failed: {ex}')
            response.success = False
            response.message = f'enable_motors failed: {ex}'
            return response
        self.get_logger().info('Stepper motors ENABLED (holding torque on, GRBL $1=255)')
        response.success = True
        response.message = 'Motors enabled (holding torque on)'
        return response

    def disable_motors_callback(self, request, response):
        try:
            with self._motor_cmd_lock:
                self._motors_enabled = False
                self._last_sent_cmd_deg = None
            # Wait for planner idle and send $1=0 without holding _motor_cmd_lock so
            # joint_states publishing is not stalled for the whole wait.
            planner_idle = self.robot.disableAllMotors()
            if not planner_idle:
                self.get_logger().warn(
                    'GRBL did not reach Idle before $1=0 (timeout). '
                    'Motors may stay engaged until the planner finishes or you power-cycle. '
                    'If this repeats, confirm firmware reports status Idle and nothing else streams G-code.'
                )
        except Exception as ex:
            with self._motor_cmd_lock:
                self._motors_enabled = True
            self.get_logger().error(f'disable_motors failed: {ex}')
            response.success = False
            response.message = f'disable_motors failed: {ex}'
            return response
        self.get_logger().info('Stepper motors DISABLED (holding torque off, GRBL $1=0)')
        response.success = True
        response.message = 'Motors disabled (holding torque off)'
        return response


def main(args=None):
    rclpy.init(args=args)

    driver = Driver()
    
    rclpy.spin(driver)

    driver.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

