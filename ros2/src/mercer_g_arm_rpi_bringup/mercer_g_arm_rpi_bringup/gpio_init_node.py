import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

from pi_gpio_interface.action import GPIO


class GPIOInitNode(Node):
    def __init__(self):
        super().__init__('gpio_init_node')

        self.client = ActionClient(self, GPIO, '/pi_gpio_server')

        # GPIO init sequence
        self.goals = [
            "17,low",
            "18,high",
            "27,high",
        ]

        self.index = 0
        self.timer = self.create_timer(0.5, self._try_send_next)

    def _try_send_next(self):
        if self.index >= len(self.goals):
            self.get_logger().info("GPIO initialization complete.")
            self.timer.cancel()
            return

        if not self.client.wait_for_server(timeout_sec=0.1):
            self.get_logger().info("Waiting for GPIO action server...")
            return

        goal = GPIO.Goal()
        goal.gpio = self.goals[self.index]

        self.get_logger().info(f"Sending GPIO goal: {goal.gpio}")
        self.client.send_goal_async(goal)

        self.index += 1


def main():
    rclpy.init()
    node = GPIOInitNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
