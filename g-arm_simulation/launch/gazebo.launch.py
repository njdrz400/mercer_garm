#!/usr/bin/env python3

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
import xacro


def generate_launch_description():
    # Get the launch directory
    pkg_garm_simulation = get_package_share_directory('g-arm_simulation')
    pkg_garm_description = get_package_share_directory('g_arm_description')
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time')
    world = LaunchConfiguration('world')
    
    # Declare launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true')
    
    declare_world_cmd = DeclareLaunchArgument(
        'world',
        default_value=[os.path.join(pkg_garm_simulation, 'worlds', 'empty.world')],
        description='Full path to world model file to load')
    
    # Process the URDF file
    robot_description_path = os.path.join(
        pkg_garm_simulation,
        'urdf',
        'g_arm_gazebo.urdf.xacro'
    )
    robot_description_config = xacro.process_file(robot_description_path)
    robot_description = {'robot_description': robot_description_config.toxml()}
    
    # Robot State Publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[robot_description, {'use_sim_time': use_sim_time}]
    )
    
    # Joint State Publisher (for manual control if needed)
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        parameters=[{'use_sim_time': use_sim_time}]
    )
    
    # Gazebo (using ros_gz_sim for Gazebo Garden)
    # Combine world path and -r flag into a single string with proper spacing
    gz_args = PythonExpression(["'", world, "' + ' -r'"])
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory('ros_gz_sim'), 'launch', 'gz_sim.launch.py')
        ]),
        launch_arguments={
            'gz_args': gz_args
        }.items()
    )
    
    # Spawn the robot in Gazebo
    spawn_entity = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'g_arm',
            '-x', '0.0',
            '-y', '0.0',
            '-z', '0.1'
        ],
        output='screen'
    )
    
    # Load controllers
    load_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
             'joint_state_broadcaster'],
        output='screen'
    )
    
    load_garm_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
             'g_arm_controller'],
        output='screen'
    )
    
    return LaunchDescription([
        declare_use_sim_time_cmd,
        declare_world_cmd,
        gz_sim,
        robot_state_publisher_node,
        joint_state_publisher_node,
        spawn_entity,
        load_joint_state_broadcaster,
        load_garm_controller,
    ])

