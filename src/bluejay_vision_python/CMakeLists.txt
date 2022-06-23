cmake_minimum_required(VERSION 3.0.2)

project(bluejay_vision_python)

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
  cv_bridge
)

find_package( OpenCV REQUIRED )

catkin_package(
    CATKIN_DEPENDS roscpp rospy std_msgs geometry_msgs
    mavros mavros_extras mavros_msgs cv_bridge
)

##include_directories(
##  ~/softwareai7/devel/include
##  ${OpenCV_INCLUDE_DIRS}
##)

catkin_install_python(PROGRAMS src/vision.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


