cmake_minimum_required(VERSION 3.0.2)
project(bluejay_actionlibs)

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
    LIBRARIES bluejay_actionlibs
    CATKIN_DEPENDS roscpp rospy std_msgs actionlib_msgs actionlib
    mavros mavros_extras mavros_msgs geometry_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ~/softwareai7/devel/include
)

add_executable(bluejay_actionlibs_takeoff src/takeoff_server.cpp)
add_executable(bluejay_actionlibs_landing src/landing_server.cpp)
add_executable(bluejay_actionlibs_navigate src/navigate_server.cpp)
add_executable(bluejay_actionlibs_move src/move_server.cpp)

add_dependencies(bluejay_actionlibs_takeoff ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(bluejay_actionlibs_landing ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(bluejay_actionlibs_navigate ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(bluejay_actionlibs_move ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(bluejay_actionlibs_takeoff ${catkin_LIBRARIES})
target_link_libraries(bluejay_actionlibs_landing ${catkin_LIBRARIES})
target_link_libraries(bluejay_actionlibs_navigate ${catkin_LIBRARIES})
target_link_libraries(bluejay_actionlibs_move ${catkin_LIBRARIES})
