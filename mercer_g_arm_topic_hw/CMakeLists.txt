cmake_minimum_required(VERSION 3.8)
project(mercer_g_arm_topic_hw)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(include)

add_library(mercer_g_arm_topic_hw SHARED
  src/topic_system.cpp
)

ament_target_dependencies(mercer_g_arm_topic_hw
  rclcpp
  hardware_interface
  pluginlib
  sensor_msgs
)

pluginlib_export_plugin_description_file(hardware_interface mercer_g_arm_topic_hw_plugins.xml)

install(
  TARGETS mercer_g_arm_topic_hw
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
)

install(FILES mercer_g_arm_topic_hw_plugins.xml
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

