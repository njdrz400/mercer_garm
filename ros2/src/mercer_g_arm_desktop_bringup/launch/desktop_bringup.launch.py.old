import os
from ament_index_python.packages import get_package_share_path

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition, UnlessCondition
from launch.substitutions import Command, LaunchConfiguration

from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():

    package_path = get_package_share_path('g_arm_description')
    default_model_path = os.path.join(package_path, 'urdf', 'robot_electromagnet.urdf.xacro')
    default_rviz_config_path = os.path.join(package_path, 'rviz', 'urdf.rviz')

    gui_arg = DeclareLaunchArgument(name='gui', default_value='true', choices=['true', 'false'],
                                    description='Flag to enable joint_state_publisher_gui')
    model_arg = DeclareLaunchArgument(name='model', default_value=str(default_model_path),
                                      description='Absolute path to robot urdf file')
    rviz_arg = DeclareLaunchArgument(name='rvizconfig', default_value=str(default_rviz_config_path),
                                     description='Absolute path to rviz config file')

    robot_description = ParameterValue(Command(['xacro ', LaunchConfiguration('model')]),
                                       value_type=str)
    # Get package paths
    #package_path = get_package_share_path('mercer_g-arm_desktop_bringup')
    
    # Default paths (can be overridden via launch arguments)
    # default_model_path = os.path.join(
    #     get_package_share_path('g_arm_description'), 
    #     'urdf', 
    #     'robot.urdf.xacro'
    # )
 

    default_rviz_config_path = os.path.join(
        get_package_share_path('g_arm_description'), 
        'rviz', 
        'urdf.rviz'
    )

    # Launch arguments
    gui_arg = DeclareLaunchArgument(
        name='gui', 
        default_value='true', 
        choices=['true', 'false'],
        description='Flag to enable joint_state_publisher_gui'
    )
    
    model_arg = DeclareLaunchArgument(
        name='model', 
        default_value=str(default_model_path),
        description='Absolute path to robot urdf file'
    )
    
    rviz_arg = DeclareLaunchArgument(
        name='rvizconfig', 
        default_value=str(default_rviz_config_path),
        description='Absolute path to rviz config file'
    )
    
    use_rviz_arg = DeclareLaunchArgument(
        name='use_rviz',
        default_value='true',
        choices=['true', 'false'],
        description='Flag to enable RViz'
    )
    
    use_rqt_arg = DeclareLaunchArgument(
        name='use_rqt',
        default_value='true',
        choices=['true', 'false'],
        description='Flag to enable RQT'
    )

    # Robot description
    robot_description = ParameterValue(
         Command(['xacro ', LaunchConfiguration('model')]),
         value_type=str
     )

    # Robot State Publisher
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description}]
        
    )

    # Joint State Publisher (depending on gui parameter)
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        condition=UnlessCondition(LaunchConfiguration('gui'))
    )

    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        condition=IfCondition(LaunchConfiguration('gui'))
        
    )

    # RViz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
        condition=IfCondition(LaunchConfiguration('use_rviz'))
    )

    # RQT
    rqt_node = Node(
        package='rqt_gui',
        executable='rqt_gui',
        name='rqt',
        output='screen',
        condition=IfCondition(LaunchConfiguration('use_rqt'))
    )

    return LaunchDescription([
        gui_arg,
        model_arg,
        rviz_arg,
        use_rviz_arg,
        use_rqt_arg,
        joint_state_publisher_node,
        joint_state_publisher_gui_node,
        robot_state_publisher_node,
        rviz_node,
        rqt_node
    ])


