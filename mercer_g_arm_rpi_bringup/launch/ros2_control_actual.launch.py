import os

from launch_ros.parameter_descriptions import ParameterValue

from launch import LaunchDescription
from launch.actions import RegisterEventHandler, TimerAction
from launch.event_handlers import OnProcessStart
from launch.substitutions import Command, PathJoinSubstitution, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from ament_index_python.packages import get_package_share_path

def generate_launch_description():
    # use_fake_hardware_arg = DeclareLaunchArgument(
    #    "use_fake_hardware",
    #    default_value="false",
    #    description="Use ros2_control fake hardware (mock_components) if true.")


    # use_fake_hardware = LaunchConfiguration("use_fake_hardware")

    package_path = get_package_share_path('g_arm_moveit2')

    default_model_path = os.path.join(package_path, 'config', 'g_arm.urdf.xacro')

    model_arg = DeclareLaunchArgument(name='model', default_value=str(default_model_path),
                                      description='Absolute path to robot urdf file')

    robot_description = ParameterValue(Command(['xacro ', LaunchConfiguration('model')]),
                                       value_type=str)


    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        output="screen",
        parameters=[
            {'robot_description': robot_description},
            PathJoinSubstitution([FindPackageShare("mercer_g_arm_rpi_bringup"), "config", "controllers.yaml"]),
        ],
    )

    # jspawner = Node(
    #     package="controller_manager",
    #     executable="spawner",
    #     arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
    #     output="screen",
    # )

    arm_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["arm_controller", "--controller-manager", "/controller_manager"],
        output="screen",
    )

    start_spawners = RegisterEventHandler(
        OnProcessStart(
            target_action=ros2_control_node,
            on_start=[
                #TimerAction(period=1.0, actions=[jspawner]),
                TimerAction(period=2.0, actions=[arm_spawner]),
            ],
        )
    )

    return LaunchDescription([
        #DeclareLaunchArgument("use_fake_hardware", default_value="true"),  # include if you want arg
        #use_fake_hardware_arg,
        model_arg,
        ros2_control_node,
        start_spawners,
    ])