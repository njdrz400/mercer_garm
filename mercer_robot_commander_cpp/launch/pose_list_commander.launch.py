from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Default: use waypoints from source config (edit without reinstalling)
    default_waypoints = '/home/scott/mercer_garm_ws/src/mercer_robot_commander_cpp/config/waypoints_example.yaml'

    waypoints_arg = DeclareLaunchArgument(
        'waypoints_file',
        default_value=default_waypoints,
        description='YAML file with waypoints list (waypoints and path)',
    )
    interface_arg = DeclareLaunchArgument(
        'interface',
        default_value='true',
        description='Run the pose list commander GUI interface',
    )
    timeout_arg = DeclareLaunchArgument(
        'timeout_sec',
        default_value='60.0',
        description='Goal timeout in seconds (per waypoint and return-to-start)',
    )

    commander_node = Node(
        package='mercer_robot_commander_cpp',
        executable='pose_list_commander_node.py',
        name='pose_list_commander',
        output='screen',
        parameters=[{
            'waypoints_file': LaunchConfiguration('waypoints_file'),
            'timeout_sec': LaunchConfiguration('timeout_sec'),
        }],
        arguments=['--ros-args', '--log-level', 'info'],
    )

    interface_node = Node(
        package='mercer_robot_commander_cpp',
        executable='pose_list_commander_interface.py',
        name='pose_list_commander_interface',
        output='screen',
        condition=IfCondition(LaunchConfiguration('interface')),
        arguments=['--ros-args', '--log-level', 'info'],
    )

    return LaunchDescription([
        waypoints_arg,
        interface_arg,
        timeout_arg,
        commander_node,
        interface_node,
    ])
