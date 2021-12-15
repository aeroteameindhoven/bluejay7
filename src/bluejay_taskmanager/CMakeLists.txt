cmake_minimum_required(VERSION 3.0.2)
project(bluejay_taskmanager)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  actionlib_msgs
  actionlib
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES bluejay_taskmanager
  CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}
)

add_executable(bluejay_taskmanager src/taskmanager.cpp)
add_dependencies(bluejay_taskmanager ${catkin_EXPORTED_TARGETS})
target_link_libraries(bluejay_taskmanager ${catkin_LIBRARIES})


