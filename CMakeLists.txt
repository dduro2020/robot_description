cmake_minimum_required(VERSION 3.8)
project(robot_description)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)

set(dependencies
  geometry_msgs
  rclcpp
)

add_executable(speed_controller_node src/speed_controller.cpp)
ament_target_dependencies(speed_controller_node ${dependencies})

install(DIRECTORY config launch meshes rviz urdf robots src DESTINATION share/${PROJECT_NAME})

install(TARGETS
  ${plugin_libs}
  speed_controller_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_package()
