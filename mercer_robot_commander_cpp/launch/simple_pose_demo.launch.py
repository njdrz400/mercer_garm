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

    # Planning scene monitor parameters
    planning_scene_monitor_parameters = {
        "publish_robot_description": False,
        "publish_robot_description_semantic": True,
        "publish_planning_scene": True,
        "publish_geometry_updates": True,
        "publish_trasforms_updates": True
    }

    # Start the move_group node (required for MoveGroupInterface)
    move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[moveit_parameters, planning_scene_monitor_parameters],
        arguments=['--ros-args', '--log-level', 'info'],
    )
  
    # Create the node with MoveIt parameters
    simple_pose_demo_node = Node(
        package="mercer_robot_commander_cpp",
        executable="simple_pose_demo",
        name="simple_pose_demo",
        output="screen",
        parameters=[moveit_parameters],
        arguments=['--ros-args', '--log-level', 'info']
    )

    return LaunchDescription([
        move_group_node,
        simple_pose_demo_node,
    ])
