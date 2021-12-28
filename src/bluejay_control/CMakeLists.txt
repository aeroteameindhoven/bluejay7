cmake_minimum_required(VERSION 3.0.2)
project(bluejay_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  dynamic_reconfigure
  tf
  pcl_ros
  mavros
  mavros_extras
  mavros_msgs
  mavlink
)

generate_dynamic_reconfigure_options(
  resource/Control.cfg
)

catkin_package(
    CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
    mavros mavros_extras mavros_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
)

add_executable(bluejay_control src/offb_controller_node.cpp)
add_dependencies(bluejay_control ${PROJECT_NAME}_gencfg)
target_link_libraries(bluejay_control ${catkin_LIBRARIES})



