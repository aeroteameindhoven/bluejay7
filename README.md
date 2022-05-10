# Installation Instruction: Setting up the development environment and simulation
# For Ubuntu 18.04 or above (Note: Ubuntu version > 20 might have problem with apt keys)

## Install ROS Melodic/Noetic
    http://wiki.ros.org/ROS/Installation
## Clone this folder into your Ubuntu homefolder

## Copy the file ubuntu_sim_ros.sh into your home folder and run it.
On how to run a script in Ubuntu.
    https://www.cyberciti.biz/faq/run-execute-sh-shell-script/
This script will install Gazebo + MAVROS + MAVLINK
If you already have MavRos + Mavlink installed, copy the file mavros_install.sh into your home folder and run it instead.

## Install QGroundControl for manual control of the simulated drone
    https://docs.qgroundcontrol.com/master/en/getting_started/download_and_install.html

## Install the PX4 flight controller + Tools
1. Git clone from this folder
    https://github.com/PX4/PX4-Autopilot
2. In the terminal, go to the newly cloned folder and run the below command
    DONT_RUN=1 make px4_sitl_default gazebo
*In case of missing packages, go through the error msgs and install the missing packages. Repeat this step until you have all the required packages
3. After finishing all the steps above, run this command:
    source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
    
## Set up development environment
1. Open up a new terminal 
2. In the new terminal run: 
    sudo gedit .bashrc
3. This will takes you to a new text file. In this text file, copy the lines below
```
#environment variable
export PX4_PATH="/home/<Your home folder here>/PX4-Autopilot"
#source ROS workspace 
source ~/softwareai7/devel/setup.bash
#PX4 sourcing
source $PX4_PATH/Tools/setup_gazebo.bash $PX4_PATH $PX4_PATH/build/px4_sitl_default
```

## To launch the entire project:
    roslaunch bluejay_launch bluejay_sitl.launch 