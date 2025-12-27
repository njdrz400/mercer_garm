from setuptools import setup
import os
from glob import glob

from launch import LaunchDescription
from launch.actions import TimerAction
from launch_ros.actions import Node


def generate_launch_description():

    # --- Node: pi_gpio_server ---
    gpio_node = Node(
        package="pi_gpio",
        executable="pi_gpio_server",
        name="pi_gpio_server",
        output="screen"
    )

    # --- Node: g_arm driver ---
    garm_node = Node(
        package="g_arm",
        executable="driver",
        name="g_arm_driver",
        output="screen",
        parameters=[
            {"X_ZERO_REAL_ANGLE_DEFAULT": 115.0}
        ],
    )

    #
    # OPTIONAL: delay node start until system hardware/network is ready
    # (equivalent to `sleep 5`)
    #
    delayed_start = TimerAction(
        period=5.0,   # seconds
        actions=[gpio_node, garm_node]
    )

    return LaunchDescription([
        garm_node,
        gpio_node,
        delayed_start
    ])

