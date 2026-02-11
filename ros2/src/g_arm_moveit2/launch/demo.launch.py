import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.conditions import IfCondition, UnlessCondition
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder
from launch_param_builder import ParameterBuilder

def generate_launch_description():

    # Command-line arguments
    tutorial_arg = DeclareLaunchArgument(
        "rviz_tutorial", default_value="True", description="Tutorial flag"
    )

    db_arg = DeclareLaunchArgument(
        "db", default_value="True", description="Enable SQLite warehouse database"
    )
    
    warehouse_db_path_arg = DeclareLaunchArgument(
        "warehouse_db_path",
        default_value=os.path.join(os.path.expanduser("~"), ".ros", "g_arm_warehouse.db"),
        description="Path to SQLite warehouse database file"
    )

    ros2_control_hardware_type = DeclareLaunchArgument(
        "ros2_control_hardware_type",
        default_value="mock_components",
        description="ROS2 control hardware interface type to use for the launch file -- possible values: [mock_components, isaac]",
    )

    moveit_config = (
        MoveItConfigsBuilder("g_arm", package_name="g_arm_moveit2")
        .robot_description(
            file_path="config/g_arm.urdf.xacro",
            mappings={
                "ros2_control_hardware_type": LaunchConfiguration(
                    "ros2_control_hardware_type"
                )
            },
        )
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .robot_description_semantic(file_path="config/g_arm.srdf")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .planning_pipelines(
            pipelines=["ompl", "chomp", "pilz_industrial_motion_planner"]
        )
        .to_moveit_configs()
    )

    # Start the actual move_group node/action server
    planning_scene_monitor_parameters = {
    "publish_robot_description": True,
    "publish_robot_description_semantic": True,
    "publish_planning_scene": True,
    "publish_geometry_updates": True,
    "publish_trasforms_updates": True
    }
    
    # SQLite warehouse database configuration
    db_config = LaunchConfiguration("db")
    warehouse_db_path = LaunchConfiguration("warehouse_db_path")
    
    # Warehouse configuration for SQLite
    # Note: warehouse_host should be the path to the SQLite database file
    # For SQLite, warehouse_port is not used but can be set to 0
    warehouse_ros_config = {
        "warehouse_plugin": "warehouse_ros_sqlite::DatabaseConnection",
        "warehouse_host": warehouse_db_path,
        "warehouse_port": 0,  # Not used for SQLite, but some plugins expect it
    }
    
    # Base parameters for move_group
    move_group_base_parameters = [moveit_config.to_dict(), planning_scene_monitor_parameters]
    
    # Conditionally add warehouse config based on db flag
    # We'll use a PythonExpression to conditionally add parameters
    # For now, we'll always include it but it will only be used when db=True
    # The warehouse plugin will handle the connection
    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=move_group_base_parameters + [warehouse_ros_config],
        arguments=["--ros-args", "--log-level", "info"],
    )

    # RViz
    tutorial_mode = LaunchConfiguration("rviz_tutorial")
    rviz_base = os.path.join(
        get_package_share_directory("g_arm_moveit2"), "launch"
    )
    rviz_full_config = os.path.join(rviz_base, "moveit.rviz")
    rviz_empty_config = os.path.join(rviz_base, "moveit_empty.rviz")
    rviz_node_tutorial = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz_empty_config],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.planning_pipelines,
            moveit_config.robot_description_kinematics,
            warehouse_ros_config,  # Add warehouse config for RViz MotionPlanning plugin
        ],
        condition=IfCondition(tutorial_mode),
    )
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz_full_config],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.planning_pipelines,
            moveit_config.robot_description_kinematics,
            warehouse_ros_config,  # Add warehouse config for RViz MotionPlanning plugin
        ],
        condition=UnlessCondition(tutorial_mode),
    )

    # Static TF
    static_tf_node = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_transform_publisher",
        output="log",
        arguments=["0.0", "0.0", "0.0", "0.0", "0.0", "0.0", "world", "base_link"],
    )

    # Publish TF
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="both",
        parameters=[moveit_config.robot_description],
    )

    # ros2_control using FakeSystem as hardware
    # When using Gazebo's gz_ros2_control plugin, the controller manager is already running
    # so we don't need to start another ros2_control_node
    ros2_controllers_path = os.path.join(
        get_package_share_directory("g_arm_moveit2"),
        "config",
        "ros2_controllers.yaml",
    )
    
    # Only start ros2_control_node if NOT using Gazebo hardware
    # When using gz_ros2_control/GazeboSimSystem, Gazebo already provides the controller manager
    ros2_control_hardware_type_config = LaunchConfiguration("ros2_control_hardware_type")
    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[moveit_config.robot_description, ros2_controllers_path],
        output="screen",
        # Don't start ros2_control_node when using Gazebo hardware - it's already provided by Gazebo
        condition=UnlessCondition(
            PythonExpression([
                "'", ros2_control_hardware_type_config, "' == 'gz_ros2_control/GazeboSimSystem'"
            ])
        ),
    )

    # Controller spawners
    joint_state_broadcaster_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--controller-manager",
            "/controller_manager",
        ],
    )

    g_arm_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["arm_controller", "-c", "/controller_manager"],
    )

    g_arm_tool_controller_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["tool_controller", "-c", "/controller_manager"],
    )

    # Warehouse SQLite database configuration is now included in move_group_node parameters above
    '''
    ####### FOR USING MOVEIT SERVO SERVER ########
    
    # Get parameters for the Servo node
    servo_params = (
        ParameterBuilder("moveit_servo")
        .yaml(
            parameter_namespace="moveit_servo",
            file_path="config/panda_simulated_config.yaml",
        )
        .to_dict()
    )
    
    '''
    return LaunchDescription(
        [
            tutorial_arg,
            db_arg,
            warehouse_db_path_arg,
            ros2_control_hardware_type,
            rviz_node,
            rviz_node_tutorial,
            static_tf_node,
            robot_state_publisher,
            move_group_node,
            ros2_control_node,
            joint_state_broadcaster_spawner,
            g_arm_controller_spawner,
            g_arm_tool_controller_spawner,
        ]
    )
