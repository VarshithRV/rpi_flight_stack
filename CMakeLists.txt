cmake_minimum_required(VERSION 3.8)
project(rpi_flight_stack)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(std_msgs REQUIRED) # depedency list
  find_package(rclcpp REQUIRED)

  add_executable(talker src/simple_publisher.cpp) # Linking the cpp file to the executable name
  ament_target_dependencies(talker rclcpp std_msgs) # talking about the depedencies for compiling the executable
  
  install(TARGETS # so that ros2 can find the executable
    talker
    DESTINATION lib/$(PROJECT_NAME)
  )
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
