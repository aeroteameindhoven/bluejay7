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
  mavros
  mavros_extras
  mavros_msgs
  mavlink
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES bluejay_taskmanager
  CATKIN_DEPENDS roscpp rospy std_msgs actionlib_msgs actionlib mavros geometry_msgs mavros_extras mavros_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
)

add_executable(bluejay_taskmanager_node src/taskmanager_node.cpp
                                        src/takeoffclient.cpp
                                        src/task.cpp
                                        src/landingclient.cpp
                                        src/fakeclient.cpp)

add_dependencies(bluejay_taskmanager_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(bluejay_taskmanager_node ${catkin_LIBRARIES})


