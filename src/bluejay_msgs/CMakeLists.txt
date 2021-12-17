cmake_minimum_required(VERSION 3.0.2)
project(bluejay_msgs)

find_package(catkin REQUIRED COMPONENTS
    std_msgs
    message_generation
)

find_package(catkin REQUIRED genmsg actionlib_msgs actionlib message_generation)
add_action_files(DIRECTORY action FILES   Landing.action
                                          TakeOff.action
                                          Navigate.action)
generate_messages(DEPENDENCIES actionlib_msgs
                               std_msgs)

catkin_package(
    LIBRARIES bluejay_msgs
    CATKIN_DEPENDS std_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

