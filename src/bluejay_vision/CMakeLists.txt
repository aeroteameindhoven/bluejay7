cmake_minimum_required(VERSION 3.0.2)

project(bluejay_vision)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  pcl_ros
  mavros
  mavros_extras
  mavros_msgs
  mavlink
)

find_package( OpenCV REQUIRED )

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
    mavros mavros_extras mavros_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
  ${OpenCV_INCLUDE_DIRS} 
)

add_executable(bluejay_vision src/vision.cpp)
add_dependencies(bluejay_vision ${PROJECT_NAME})
target_link_libraries(bluejay_vision ${catkin_LIBRARIES} ${OpenCV_LIBS})




