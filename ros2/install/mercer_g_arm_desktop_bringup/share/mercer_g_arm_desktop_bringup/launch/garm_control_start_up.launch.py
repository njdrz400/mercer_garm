import os
from ament_index_python.packages import get_package_share_path, get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource


from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue

from moveit_configs_utils import MoveItConfigsBuilder
from launch_param_builder import ParameterBuilder

from setuptools import setup
from glob import glob
from launch.actions import TimerAction


from launch.actions import DeclareLaunchArgument, RegisterEventHandler, TimerAction, ExecuteProcess
from launch.event_handlers import OnProcessStart, OnProcessExit
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    package_path = get_package_share_path('g_arm_description')
    default_model_path = os.path.join(package_path, 'urdf', 'robot_electromagnet.urdf.xacro')

    model_arg = DeclareLaunchArgument(name='model', default_value=str(default_model_path),
                                      description='Absolute path to robot urdf file')

    robot_description = ParameterValue(Command(['xacro ', LaunchConfiguration('model')]),
                                       value_type=str)
    moveit_config = (
        MoveItConfigsBuilder("g_arm", package_name="g_arm_moveit2")
        .robot_description(file_path="config/g_arm.urdf.xacro")
        .robot_description_semantic(file_path="config/g_arm.srdf")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )
  
   


    # Publish TF
    robot_state_publisher_node= Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="screen",
        parameters=[moveit_config.robot_description,
        {'use_sim_time': False,
        'ignore_timestamp': True}
        ],
    )


    #joint_state_publisher_node = Node(
    #      package='joint_state_publisher',
    ##    executable='joint_state_publisher',
    #    parameters=[{'robot_description': robot_description}],
    #    output="screen"     
    #)

    # Static TF
    static_tf_node = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="screen",
        arguments=["0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "world", "base_link"],
    )


   

    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[PathJoinSubstitution([FindPackageShare('mercer_g_arm_rpi_bringup'), 'config', 'controllers.yaml'])],
        remappings=[("~/robot_description", "/robot_description")],
        arguments=['--ros-args', '--log-level', 'info'],
        output="screen",
    )

    # Start ros2_control_node after g_arm node starts
    start_ros2_control = RegisterEventHandler(
        OnProcessStart(
            target_action=static_tf_node,
            on_start=[
                TimerAction(
                    period=5.0,
                    actions=[ros2_control_node]),
            ],
        )
    )
   

    # Joint state broadcaster spawner (required for MoveIt)
#    joint_state_broadcaster_spawner = ExecuteProcess(
#        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'joint_state_broadcaster', '--controller-manager', '/controller_manager'],
#        output='screen',
#    )

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

    # Start joint_state_broadcaster first after ros2_control_node starts
#    start_joint_state_broadcaster = RegisterEventHandler(
#        OnProcessStart(
#            target_action=ros2_control_node,
#            on_start=[
#                TimerAction(
#                    period=10.0,
#                    actions=[joint_state_broadcaster_spawner]
#                ),
#            ],
#        )
#    )

    # Start arm_controller after joint_state_broadcaster completes
    start_arm_controller = RegisterEventHandler(
        OnProcessStart(
            target_action=ros2_control_node, #joint_state_broadcaster_spawner,
            on_start=[
                TimerAction(
                    period=2.0,
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

    # Go-to-pose action server (move_group + go_to_pose_server), started after controllers are up
    go_to_pose_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory('mercer_robot_commander_cpp'), 'launch', 'go_to_pose_server.launch.py')
        ])
    )
    start_go_to_pose_server = RegisterEventHandler(
        OnProcessExit(
            target_action=magnet_controller_spawner,
            on_exit=[
                TimerAction(
                    period=3.0,
                    actions=[go_to_pose_server_launch]
                ),
            ],
        )
    )

    return LaunchDescription([
#        robot_description,
   
 #       delayed_start,
        model_arg,
        #joint_state_publisher_node,
        robot_state_publisher_node,
        static_tf_node,
        #gpio_init
        start_ros2_control,
 #       start_joint_state_broadcaster,
        start_arm_controller,
        start_magnet_controller,
        start_go_to_pose_server,
    ])



