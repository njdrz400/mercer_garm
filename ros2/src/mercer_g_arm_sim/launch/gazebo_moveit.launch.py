#!/usr/bin/env python3

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # Get the launch directory
    pkg_garm_simulation = get_package_share_directory('mercer_g_arm_sim')
    pkg_garm_moveit2 = get_package_share_directory('g_arm_moveit2')
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')
    
    # Declare launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation (Gazebo) clock if true')
    
    # Gazebo removed - launching MoveIt2 only
    
    # Add world objects to MoveIt2's planning scene for RViz visualization
    # This publishes the world objects (like tiny_wall) as collision objects
    # so they appear in RViz when MoveIt2 is running
    add_world_to_scene = Node(
        package='mercer_g_arm_sim',
        executable='add_world_to_planning_scene',
        name='mercer_g_arm_sim_add_world_to_planning_scene',
        output='screen'
    )

    # Add 300 mm x 300 mm grid (50 mm spacing, 5 mm thick) as collision objects
    # so the robot can plan around the grid
    add_grid_to_scene = Node(
        package='mercer_g_arm_sim',
        executable='add_grid_to_planning_scene',
        name='add_grid_to_planning_scene',
        output='screen'
    )
    
    # Note: With ros2_control properly configured, joint states should be published
    # automatically through the controller manager. However, we may need a bridge
    # if ros2_control is not working. Let's comment this out for now and see if
    # ros2_control handles it.
    # If joint states are not published, uncomment and fix the bridge below:
    # joint_state_bridge = Node(
    #     package='ros_gz_bridge',
    #     executable='parameter_bridge',
    #     arguments=[
    #         '/model/g_arm/joint_state@sensor_msgs/msg/JointState[gz.msgs.Model'
    #     ],
    #     output='screen',
    #     remappings=[
    #         ('/model/g_arm/joint_state', '/joint_states')
    #     ]
    # )
    
    # Include MoveIt2 launch
    # Launch MoveIt2 directly without Gazebo
    moveit_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(pkg_garm_moveit2, 'launch', 'demo.launch.py')
        ]),
        launch_arguments={
            'use_sim_time': use_sim_time,
            'ros2_control_hardware_type': 'mock_components',  # Use mock components when not using Gazebo
            'rviz_tutorial': 'False',  # Use full RViz config, not tutorial mode
        }.items()
    )
    
    return LaunchDescription([
        declare_use_sim_time_cmd,
        moveit_launch,  # Launch MoveIt2 directly
        # Add world objects to planning scene after MoveIt2 starts
        TimerAction(
            period=2.0,  # Wait for MoveIt2 to fully initialize
            actions=[add_world_to_scene]
        ),
        # Add grid collision object after world
        TimerAction(
            period=3.0,
            actions=[add_grid_to_scene]
        ),
    ])

