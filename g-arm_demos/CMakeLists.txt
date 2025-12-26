cmake_minimum_required(VERSION 3.8)
project(g-arm_demos)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# Install notebooks and demos
install(DIRECTORY notebooks
  DESTINATION share/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.ipynb"
)

install(DIRECTORY demos
  DESTINATION share/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.py"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

