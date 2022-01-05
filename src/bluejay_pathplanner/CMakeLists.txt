cmake_minimum_required(VERSION 3.0.2)
project(bluejay_pathplanner)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  mavros
  mavros_extras
  mavros_msgs
  mavlink
)


catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
    mavros mavros_extras mavros_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
)


add_executable(bluejay_pathplanner src/globalplanner.cpp)
add_dependencies(bluejay_pathplanner ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(bluejay_pathplanner ${catkin_LIBRARIES})






