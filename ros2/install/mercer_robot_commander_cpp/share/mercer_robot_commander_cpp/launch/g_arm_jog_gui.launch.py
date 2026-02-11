from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    """Launch the G-Arm Jog GUI node"""
    
    jog_gui_node = Node(
        package="mercer_robot_commander_cpp",
        executable="g_arm_jog_gui.py",
        name="g_arm_jog_gui",
        output="screen",
        arguments=['--ros-args', '--log-level', 'info']
    )
    
    return LaunchDescription([
        jog_gui_node,
    ])
