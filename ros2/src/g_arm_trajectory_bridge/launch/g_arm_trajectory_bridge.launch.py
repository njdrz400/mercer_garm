# from launch import LaunchDescription
# from launch_ros.actions import Node
# #ros2/g_arm_moveit2/config/moveit_controllers.yaml
# def generate_launch_description():
#     return LaunchDescription([
#         Node(
#             package='g_arm_trajectory_bridge',
#             executable='bridge',                 # <- matches setup.py entry_points
#             name='g_arm_trajectory_bridge',
#             output='screen',
#             parameters=[{
#                 'rate_hz': 20.0,
#                 'joints': ['joint1', 'joint2', 'joint3', 'electromagnet'],
#             }],
#         )
#     ])

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    pkg = get_package_share_directory('g_arm_moveit2')
    moveit_controllers = os.path.join(pkg, 'config', 'moveit_controllers.yaml')

    move_group = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[
            # your existing moveit_config parameters...
            moveit_controllers,  # <-- ensures MoveIt loads the controllers
        ],
    )

    return LaunchDescription([move_group])
