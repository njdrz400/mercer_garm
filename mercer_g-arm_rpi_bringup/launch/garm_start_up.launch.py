from setuptools import setup
import os
from glob import glob

from launch import LaunchDescription
from launch.actions import TimerAction
from launch_ros.actions import Node


def generate_launch_description():

    package_path = get_package_share_path('g_arm_description')
    default_model_path = os.path.join(package_path, 'urdf', 'robot_electromagnet.urdf.xacro')

    model_arg = DeclareLaunchArgument(name='model', default_value=str(default_model_path),
                                      description='Absolute path to robot urdf file')


    robot_description = ParameterValue(Command(['xacro ', LaunchConfiguration('model')]),
                                       value_type=str)

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}]
    )


    # --- Node: pi_gpio_server ---
    gpio_node = Node(
        package="pi_gpio",
        executable="pi_gpio_server",
        name="pi_gpio_server",
        output="screen"
    )

    # --- Node: g_arm driver ---
    garm_node = Node(
        package="g_arm",
        executable="driver",
        name="g_arm_driver",
        output="screen",
        parameters=[
            {"X_ZERO_REAL_ANGLE_DEFAULT": 115.0}
        ],
    )

    #
    # OPTIONAL: delay node start until system hardware/network is ready
    # (equivalent to `sleep 5`)
    #
    delayed_start = TimerAction(
        period=5.0,   # seconds
        actions=[gpio_node, garm_node]
    )

    return LaunchDescription([
        garm_node,
        gpio_node,
        delayed_start,
        model_arg,
        joint_state_publisher_node,
        robot_state_publisher_node,
    ])

