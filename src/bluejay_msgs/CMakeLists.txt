cmake_minimum_required(VERSION 3.0.2)
project(bluejay_msgs)

find_package(catkin REQUIRED COMPONENTS
    std_msgs
    message_generation
    genmsg
    actionlib_msgs
    actionlib
    geometry_msgs
    rospy
    roscpp
    trajectory_msgs
)

add_action_files(DIRECTORY action FILES   Landing.action
                                          TakeOff.action
                                          Move.action
                                          Circle.action
                                          Navigate.action)
generate_messages(DEPENDENCIES geometry_msgs
                               actionlib_msgs
                               std_msgs
                               trajectory_msgs
                               )

catkin_package(
    LIBRARIES bluejay_msgs
    CATKIN_DEPENDS std_msgs message_runtime geometry_msgs trajectory_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
)

