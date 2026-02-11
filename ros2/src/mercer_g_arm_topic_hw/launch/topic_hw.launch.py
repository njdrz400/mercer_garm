import os

from ament_index_python.packages import get_package_share_path

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, RegisterEventHandler, TimerAction, ExecuteProcess
from launch.event_handlers import OnProcessStart, OnProcessExit
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # Get package paths
    # description_package_path = get_package_share_path('g_arm_moveit2')
    # #/home/rosuser/mercer_garm_ws/src/g_arm_moveit2/config/g_arm.urdf.xacro"
    # # Default URDF path
    # default_model_path = os.path.join(
    #     description_package_path, 'config', 'g_arm.urdf.xacro'
    # )

    # # Launch arguments
    # model_arg = DeclareLaunchArgument(
    #     name='model',
    #     default_value=str(default_model_path),
    #     description='Absolute path to robot urdf file'
    # )

    # # Get launch configurations
    # model = LaunchConfiguration('model')

    # # Robot description
    # robot_description = ParameterValue(
    #     Command(['xacro ', model]),
    #     value_type=str
    # )

    # ROS2 Control node
    # ros2_control_node = Node(
    #     package='controller_manager',
    #     executable='ros2_control_node',
    #     output='screen',
    #     parameters=[
    #         {'robot_description': robot_description},
    #         PathJoinSubstitution([FindPackageShare('mercer_g_arm_rpi_bringup'), 'config', 'controllers.yaml']),
    #     ],
    # )
    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[PathJoinSubstitution([FindPackageShare('mercer_g_arm_rpi_bringup'), 'config', 'controllers.yaml'])],
        remappings=[("~/robot_description", "/robot_description")],
        arguments=['--ros-args', '--log-level', 'info'],
        output="screen",
    )
    # Joint state broadcaster spawner (should be started first)
    # Using ExecuteProcess with ros2 control command for better retry handling
    #joint_state_broadcaster_spawner = ExecuteProcess(
    #    cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'joint_state_broadcaster', '--controller-manager', '/controller_manager'],
   #     output='screen',
   # )

    # Arm controller spawner  
#    /controller_manager/list_controllers

    arm_controller_spawner = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'arm_controller', '--controller-manager', '/controller_manager'],
        output='screen',
    )

    # Magnet controller spawner (optional)
    magnet_controller_spawner = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'magnet_controller', '--controller-manager', '/controller_manager'],
        output='screen',
    )

    # Register event handlers to spawn controllers after ros2_control_node starts
    # Start joint_state_broadcaster first with a longer delay to ensure controller manager is ready
    # start_joint_state_broadcaster = RegisterEventHandler(
    #     OnProcessStart(
    #         target_action=ros2_control_node,
    #         on_start=[
    #             TimerAction(
    #                 period=10.0,
    #                 actions=[joint_state_broadcaster_spawner]
    #             ),
    #         ],
    #     )
    # )

    # Start arm_controller after ros2_control_node starts
    start_arm_controller = RegisterEventHandler(
        OnProcessStart(
            target_action=ros2_control_node,
            on_start=[
                TimerAction(
                    period=10.0,
                    actions=[arm_controller_spawner]
                ),
            ],
        )
    )

    # Start magnet_controller after arm_controller completes
    start_magnet_controller = RegisterEventHandler(
        OnProcessExit(
            target_action=arm_controller_spawner,
            on_exit=[
                TimerAction(
                    period=2.0,
                    actions=[magnet_controller_spawner]
                ),
            ],
        )
    )

    return LaunchDescription([
        #model_arg,
        ros2_control_node,
        #start_joint_state_broadcaster,
        start_arm_controller,
        start_magnet_controller,
    ])

