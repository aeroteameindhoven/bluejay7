# Installation Instruction: Setting up the development environment and simulation
# For Ubuntu 18.04 or above.
## Install ROS Melodic/Noetic
    http://wiki.ros.org/ROS/Installation
## Clone this folder into your catkin workspace

## Copy the file ubuntu_sim_ros_melodic.sh into your home folder and run it.
    https://www.cyberciti.biz/faq/run-execute-sh-shell-script/
    Before running it execture this command in ur catkin_ws folder: catkin clean -y
This script will install Gazebo + MAVROS + MAVLINK

## Install QGroundControl for manual control of the simulated drone
    https://docs.qgroundcontrol.com/master/en/getting_started/download_and_install.html
## Install the PX4 flight controller + Tools
    https://github.com/PX4/PX4-Autopilot
## Run Px4 Simulation with Gazebo and ROS:
    https://docs.px4.io/master/en/simulation/ros_interface.html
## To control a simulated drone through Gazebo and px4:
    Launch QGroundControl
    Launch a drone in gazebo
    https://docs.px4.io/master/en/simulation/gazebo.html

## To launch gazebo with the current bluejay drone description:
    roslaunch bluejay_gazebo bluejay_gazebo.launch [launch gazebo]
## To launch rviz with the current bluejay drone description:
    roslaunch bluejay_description urdf.launch
