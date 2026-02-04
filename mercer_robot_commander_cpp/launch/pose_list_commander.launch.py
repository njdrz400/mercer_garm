from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_path


def generate_launch_description():
    pkg_share = get_package_share_path('mercer_robot_commander_cpp')
    default_waypoints = str(pkg_share / 'config' / 'waypoints_example.yaml')

    waypoints_arg = DeclareLaunchArgument(
        'waypoints_file',
        default_value=default_waypoints,
        description='YAML file with waypoints list (waypoints: [{x, y, z, electromagnet_on?}, ...])'
    )
    interface_arg = DeclareLaunchArgument(
        'interface',
        default_value='true',
        description='Run the pose list commander GUI interface'
    )

    commander_node = Node(
        package='mercer_robot_commander_cpp',
        executable='pose_list_commander_node.py',
        name='pose_list_commander',
        output='screen',
        parameters=[{'waypoints_file': LaunchConfiguration('waypoints_file')}],
        arguments=['--ros-args', '--log-level', 'info']
    )

    interface_node = Node(
        package='mercer_robot_commander_cpp',
        executable='pose_list_commander_interface.py',
        name='pose_list_commander_interface',
        output='screen',
        condition=IfCondition(LaunchConfiguration('interface')),
        arguments=['--ros-args', '--log-level', 'info']
    )

    return LaunchDescription([
        waypoints_arg,
        interface_arg,
        commander_node,
        interface_node,
    ])
