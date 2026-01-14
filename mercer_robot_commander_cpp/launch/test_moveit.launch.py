from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    # Use MoveItConfigsBuilder to get all required MoveIt parameters
    moveit_config = (
        MoveItConfigsBuilder("g_arm", package_name="g_arm_moveit2")
        .robot_description(file_path="config/g_arm.urdf.xacro")
        .robot_description_semantic(file_path="config/g_arm.srdf")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )

    # Convert MoveIt config to dictionary for the node
    moveit_parameters = moveit_config.to_dict()

    # Robot state publisher (publishes TF and robot description)
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="screen",
        parameters=[moveit_config.robot_description],
    )

    # Create the node with MoveIt parameters
    test_moveit_node = Node(
        package="mercer_robot_commander_cpp",
        executable="test_moveit",
        name="test_moveit",
        output="screen",
        parameters=[moveit_parameters],
    )

    return LaunchDescription([
        robot_state_publisher,
        test_moveit_node,
    ])
