#!/usr/bin/env python3
"""Launch the macropad tic-tac-toe node (Tk window + serial to macropad)."""

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='macropad_tictactoe',
            executable='macropad_tictactoe_node',
            name='macropad_tictactoe_node',
            output='screen',
        ),
    ])
