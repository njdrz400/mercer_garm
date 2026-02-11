#from launch import LaunchDescription
#from launch_ros.actions import Node


#def generate_launch_description():
#    return LaunchDescription([
#        Node(
#            package='garm_motion_planning_demos',
#            executable='garm_motion_planning_node',
#            name='garm_motion_planning_node',
#            output='screen'
#        ),
#    ])

import os
import tempfile
import yaml
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node, SetParameter, SetParametersFromFile

from moveit_configs_utils import MoveItConfigsBuilder

def launch_setup(context):
    # Use MoveItConfigsBuilder to get all required MoveIt parameters
    moveit_config = (
        MoveItConfigsBuilder("g_arm", package_name="g_arm_moveit2")
        .robot_description(file_path="config/g_arm.urdf.xacro")
        .robot_description_semantic(file_path="config/g_arm.srdf")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )
    
    package_path = get_package_share_directory('g_arm_description')
    default_rviz_config_path = os.path.join(package_path, 'rviz', 'urdf.rviz')
    
    # Get rviz config path
    rviz_config_path = LaunchConfiguration('rvizconfig').perform(context)
    if not rviz_config_path:
        rviz_config_path = default_rviz_config_path
    
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[moveit_config.robot_description]
    )

    # Depending on gui parameter, either launch joint_state_publisher or joint_state_publisher_gui
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        #condition=UnlessCondition(LaunchConfiguration('gui'))
    )

    # Convert MoveIt config to dictionary for the planning node
    # This includes all required parameters: robot_description, robot_description_semantic,
    # robot_description_kinematics, planning_pipelines, etc.
    moveit_parameters = moveit_config.to_dict()
    
    # Create a parameter file for MoveItPy to read
    # MoveItPy creates its own internal node and needs access to all parameters
    # The parameter file format: node_name: {ros__parameters: {...}}
    # Note: SetParametersFromFile applies to all nodes, so we need to be careful
    param_file = tempfile.NamedTemporaryFile(mode='w', suffix='.yaml', delete=False)
    param_file_path = None
    try:
        # ROS2 parameter file format - must have ros__parameters as a key under node name
        param_data = {
            'garm_motion_planning_node': {
                'ros__parameters': moveit_parameters
            }
        }
        # Write YAML with proper formatting
        yaml.dump(param_data, param_file, default_flow_style=False, allow_unicode=True, sort_keys=False, width=2000)
        param_file_path = param_file.name
        param_file.close()
        print(f"Created parameter file: {param_file_path}")
    except Exception as e:
        print(f"Warning: Could not create parameter file: {e}")
        import traceback
        traceback.print_exc()
        if param_file_path:
            try:
                os.remove(param_file_path)
            except:
                pass
        param_file_path = None
    
    # Create node with parameters
    garm_motion_planning_demos_node = Node(
            package='garm_motion_planning_demos',
            executable='garm_motion_planning_node',
            name='garm_motion_planning_node',
            output='screen',
            parameters=[moveit_parameters]
    )

    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', rviz_config_path],
    )

    # Use SetParametersFromFile to make parameters available globally
    # This is necessary because MoveItPy creates its own internal node and needs
    # access to all parameters including planning pipelines
    # The parameter file is node-specific, so other nodes should ignore parameters they don't need
    launch_actions = [
        robot_state_publisher_node,
        joint_state_publisher_node,
        garm_motion_planning_demos_node,
        rviz_node
    ]
    
    # Add parameter file globally so MoveItPy's internal node can access it
    if param_file_path:
        # Insert at the beginning so parameters are available before nodes start
        launch_actions.insert(0, SetParametersFromFile(param_file_path))
    
    return launch_actions

def generate_launch_description():
    package_path = get_package_share_directory('g_arm_description')
    
    rviz_arg = DeclareLaunchArgument(
        name='rvizconfig',
        default_value=str(os.path.join(package_path, 'rviz', 'urdf.rviz')),
        description='Absolute path to rviz config file'
    )
    
    return LaunchDescription([
        rviz_arg,
        OpaqueFunction(function=launch_setup)
    ])
     