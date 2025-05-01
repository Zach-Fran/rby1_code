cmake_minimum_required(VERSION 3.10)
project(rby1_base_movement)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rby1-sdk REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Eigen3 REQUIRED)

# Include rby1-sdk headers
include_directories(~/rby1-sdk/include)

# Include Eigen directories
include_directories(
  ${EIGEN3_INCLUDE_DIRS}  # Add this
  /home/nvidia/rby1-sdk/include
  ${sensor_msgs_INCLUDE_DIRS}
)

#rosidl_generate_interfaces(${PROJECT_NAME}
#  "srv/speedControl.srv"  # Ensure this matches your .srv filename
#  DEPENDENCIES sensor_msgs
#)

add_executable(rby1_base_movement_subscriber src/rby1_base_movement_subscriber.cpp)
ament_target_dependencies(rby1_base_movement_subscriber rclcpp sensor_msgs rby1-sdk)

#add_executable(speed_server src/rby1_movement_subscriber.cpp)
#ament_target_dependencies(speed_server 
#    rclcpp
#    sensor_msgs
#    rosidl_default_runtime)

target_link_libraries(rby1_base_movement_subscriber rby1-sdk::rby1-sdk)

install(TARGETS rby1_base_movement_subscriber
  DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

#ament_export_dependencies(rosidl_default_runtime)
ament_package()
