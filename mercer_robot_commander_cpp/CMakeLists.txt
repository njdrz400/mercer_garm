cmake_minimum_required(VERSION 3.8)
project(mercer_robot_commander_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(g_arm_msgs REQUIRED)

add_executable(test_moveit src/test_moveit.cpp)

ament_target_dependencies(test_moveit
  rclcpp
  moveit_ros_planning_interface
)

add_executable(commander src/commander_template.cpp)

ament_target_dependencies(commander
  rclcpp
  moveit_ros_planning_interface
  example_interfaces
  geometry_msgs
  tf2
)

add_executable(joint_space_demo src/joint_space_demo.cpp)

ament_target_dependencies(joint_space_demo
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  tf2
)

add_executable(pose_space_demo src/pose_space_demo.cpp)

ament_target_dependencies(pose_space_demo
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  tf2
)

add_executable(simple_pose_demo src/simple_pose_demo.cpp)

ament_target_dependencies(simple_pose_demo
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  tf2
)

add_executable(pose_to_joint_commander src/pose_to_joint_commander.cpp)

ament_target_dependencies(pose_to_joint_commander
  rclcpp
  moveit_ros_planning_interface
  example_interfaces
  geometry_msgs
  std_msgs
  tf2
  tf2_eigen
  tf2_geometry_msgs
)

add_executable(go_to_pose_server src/go_to_pose_server.cpp)

ament_target_dependencies(go_to_pose_server
  rclcpp
  rclcpp_action
  moveit_ros_planning_interface
  geometry_msgs
  std_msgs
  sensor_msgs
  control_msgs
  trajectory_msgs
  tf2
  tf2_ros
  tf2_eigen
  tf2_geometry_msgs
  g_arm_msgs
)

install(TARGETS
  test_moveit
  commander
  joint_space_demo
  pose_space_demo
  simple_pose_demo
  pose_to_joint_commander
  go_to_pose_server
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(PROGRAMS
  scripts/go_to_pose_client.py
  scripts/example_go_to_pose.py
  scripts/g_arm_jog_gui.py
  scripts/pose_list_commander_node.py
  scripts/pose_list_commander_interface.py
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

 