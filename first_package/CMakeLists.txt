cmake_minimum_required(VERSION 3.8)
project(first_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(enpm663_interfaces REQUIRED)

###########
# C++
###########
include_directories(include/first_package)

add_executable(publisher_cpp src/publisher_cpp.cpp)
ament_target_dependencies(publisher_cpp rclcpp example_interfaces enpm663_interfaces)

add_executable(subscriber_cpp src/subscriber_cpp.cpp)
ament_target_dependencies(subscriber_cpp rclcpp example_interfaces)

add_executable(service_add_two_ints src/service_cpp.cpp)
ament_target_dependencies(service_add_two_ints rclcpp enpm663_interfaces)

add_executable(client_add_two_ints src/client_add_two_ints.cpp)
ament_target_dependencies(client_add_two_ints rclcpp enpm663_interfaces)


install(TARGETS
publisher_cpp 
subscriber_cpp
service_add_two_ints
client_add_two_ints
DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include launch config DESTINATION share/${PROJECT_NAME})

###########
# Python
###########
# Install Python modules
ament_python_install_package(${PROJECT_NAME} SCRIPTS_DESTINATION lib/${PROJECT_NAME})

# Install Python executables
install(PROGRAMS
  nodes/publisher_py.py
  nodes/subscriber_py.py
  nodes/client_add_two_ints_py.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
