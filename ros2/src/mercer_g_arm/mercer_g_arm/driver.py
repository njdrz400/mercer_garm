import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState

import math, time
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
            
        self.get_logger().info(colored("Robot is ready to move!", "green"))
        
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.joints_state_apply)
        self.js_pub = self.create_publisher(JointState, 'joint_states', 10)


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
            
            self.robot.toolPWM(pwm)
            self.robot.setAngles(j1, j2, j3)
            
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



def main(args=None):
    rclpy.init(args=args)

    driver = Driver()
    
    rclpy.spin(driver)

    driver.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

