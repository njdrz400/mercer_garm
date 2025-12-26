#!/usr/bin/env python3

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import xacro


def generate_launch_description():
    # Get package directories
    pkg_garm_description = get_package_share_directory('g_arm_description')
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')
    
    # Declare launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation (Gazebo) clock if true')
    
    # Process the URDF file
    # Default to base robot description (can be overridden with use_gazebo_urdf argument)
    robot_description_path = os.path.join(
        pkg_garm_description,
        'urdf',
        'robot.urdf.xacro'
    )
    
    robot_description_config = xacro.process_file(robot_description_path)
    robot_description = {'robot_description': robot_description_config.toxml()}
    
    # Robot State Publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description, {'use_sim_time': use_sim_time}]
    )
    
    return LaunchDescription([
        declare_use_sim_time_cmd,
        robot_state_publisher_node,
    ])

