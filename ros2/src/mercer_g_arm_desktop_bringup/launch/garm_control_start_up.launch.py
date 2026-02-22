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


from launch.actions import DeclareLaunchArgument, RegisterEventHandler, TimerAction, GroupAction
from launch.event_handlers import OnProcessStart
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution
from launch.substitutions import PythonExpression
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    package_path = get_package_share_path('g_arm_description')
    default_model_path = os.path.join(package_path, 'urdf', 'robot_electromagnet.urdf.xacro')

    model_arg = DeclareLaunchArgument(name='model', default_value=str(default_model_path),
                                      description='Absolute path to robot urdf file')

    use_mock_hardware_arg = DeclareLaunchArgument(
        'use_mock_hardware',
        default_value='false',
        description='If true, use mock hardware (mock_components/GenericSystem) and do not start the real g_arm driver',
    )

    use_rviz_arg = DeclareLaunchArgument(
        'use_rviz',
        default_value='true',
        choices=['true', 'false'],
        description='Flag to enable RViz2',
    )

    use_rqt_arg = DeclareLaunchArgument(
        'use_rqt',
        default_value='true',
        choices=['true', 'false'],
        description='Flag to enable RQt',
    )

    usb_port_arg = DeclareLaunchArgument(
        'usb_port',
        default_value='/dev/ttyUSB0',
        description='USB port for the robot (e.g. /dev/ttyUSB0 or /dev/ttyACM0)',
    )

    x_zero_real_angle_arg = DeclareLaunchArgument(
        'x_zero_real_angle',
        default_value='135',
        description='Real angle (degrees) when robot joint 1 (X) is at zero in GRBL',
    )

    robot_description = ParameterValue(Command(['xacro ', LaunchConfiguration('model')]),
                                       value_type=str)
    
    
    # When use_mock_hardware is true, use mock_components so no real driver is needed
    ros2_control_hardware_type = PythonExpression([
        "'mock_components/GenericSystem' if '", LaunchConfiguration("use_mock_hardware"), "' == 'true' else 'mercer_g_arm_topic_hw/TopicSystem'"
    ])

    moveit_config = (
        MoveItConfigsBuilder("g_arm", package_name="g_arm_moveit2")
        .robot_description(
            file_path="config/g_arm.urdf.xacro",
            mappings={"ros2_control_hardware_type": ros2_control_hardware_type},
        )
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

  

    # Real hardware: controller config without joint_state_broadcaster (driver publishes /joint_states)
    ros2_control_node_real = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[PathJoinSubstitution([FindPackageShare('g_arm_moveit2'), 'config', 'ros2_controllers.yaml'])],
        remappings=[("~/robot_description", "/robot_description")],
        arguments=['--ros-args', '--log-level', 'info'],
        output="screen",
    )
    # Mock hardware: controller config with joint_state_broadcaster (for /joint_states + TF)
    ros2_control_node_mock = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[PathJoinSubstitution([FindPackageShare('g_arm_moveit2'), 'config', 'ros2_controllers_mock.yaml'])],
        remappings=[("~/robot_description", "/robot_description")],
        arguments=['--ros-args', '--log-level', 'info'],
        output="screen",
    )

    delayed_ros2_control_real = GroupAction(
        condition=UnlessCondition(LaunchConfiguration("use_mock_hardware")),
        actions=[TimerAction(period=5.0, actions=[ros2_control_node_real])],
    )
    delayed_ros2_control_mock = GroupAction(
        condition=IfCondition(LaunchConfiguration("use_mock_hardware")),
        actions=[TimerAction(period=5.0, actions=[ros2_control_node_mock])],
    )

    # Controller spawners (Node-based)
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "-c", "/controller_manager", "--activate"],
        output="screen",
    )

    arm_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["arm_controller", "-c", "/controller_manager", "--activate"],
        output="screen",
    )

    magnet_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["magnet_controller", "-c", "/controller_manager", "--activate"],
        output="screen",
    )

    # Mock hardware: spawn joint_state_broadcaster at 7s (for /joint_states + TF), then arm at 9s
    delayed_joint_state_broadcaster_mock = TimerAction(
        period=7.0,
        actions=[joint_state_broadcaster_spawner],
    )
    delayed_arm_controller_mock = TimerAction(
        period=9.0,
        actions=[arm_controller_spawner],
    )
    mock_controller_sequence = GroupAction(
        condition=IfCondition(LaunchConfiguration("use_mock_hardware")),
        actions=[delayed_joint_state_broadcaster_mock, delayed_arm_controller_mock],
    )
    # Real hardware: spawn arm_controller at 7s only
    delayed_arm_controller_real = TimerAction(
        period=7.0,
        actions=[arm_controller_spawner],
    )
    real_controller_sequence = GroupAction(
        condition=UnlessCondition(LaunchConfiguration("use_mock_hardware")),
        actions=[delayed_arm_controller_real],
    )

    start_magnet_controller = RegisterEventHandler(
        OnProcessStart(
            target_action=arm_controller_spawner,
            on_start=[
                TimerAction(period=2.0, actions=[magnet_controller_spawner]),
            ],
        )
    )

    # Go-to-pose action server, started 3s after magnet_controller spawner starts
    go_to_pose_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory('mercer_robot_commander_cpp'), 'launch', 'go_to_pose_server.launch.py')
        ])
    )
    start_go_to_pose_server = RegisterEventHandler(
        OnProcessStart(
            target_action=magnet_controller_spawner,
            on_start=[
                TimerAction(period=3.0, actions=[go_to_pose_server_launch]),
            ],
        )
    )

    # Real hardware driver: only start when not using mock
    garm_node = Node(
        package="mercer_g_arm",
        executable="driver",
        name="g_arm_driver",
        output="screen",
        parameters=[
            {"usb_port": LaunchConfiguration("usb_port")},
            {"X_ZERO_REAL_ANGLE": LaunchConfiguration("x_zero_real_angle")},
        ],
        condition=UnlessCondition(LaunchConfiguration("use_mock_hardware")),
    )

    # RViz2 (optional)
    default_rviz_config = os.path.join(
        get_package_share_directory('g_arm_moveit2'), 'launch', 'moveit.rviz'
    )
    
    
    return LaunchDescription([
        use_mock_hardware_arg,
        use_rviz_arg,
        use_rqt_arg,
        usb_port_arg,
        x_zero_real_angle_arg,
        model_arg,
        garm_node,
        robot_state_publisher_node,
        static_tf_node,
        delayed_ros2_control_real,
        delayed_ros2_control_mock,
        mock_controller_sequence,
        real_controller_sequence,
        start_magnet_controller,
        start_go_to_pose_server,
       
    ])



