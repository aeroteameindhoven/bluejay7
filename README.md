# Installation Instruction: Setting up the development environment and simulation
## 1 Install Ubuntu 18.04 or above (Note: Ubuntu version > 20 might have problem with apt keys (Wont work with step 2))
    https://ubuntu.com/tutorials/install-ubuntu-desktop#1-overview

## 2 Install ROS Melodic/Noetic
    http://wiki.ros.org/ROS/Installation

## 3 Install the software stack + other supporting software    
### 3.1 Clone this folder into your Ubuntu homefolder
Password for push pull etc: 
```
MKPLq5tkFeTbCjnU2mgq
```

### 3.2 Copy the file ubuntu_sim_ros.sh into your home folder and run it.
On how to run a script in Ubuntu. This script will insall MAVROS + MAVLINK + ROS
    ```
    https://www.cyberciti.biz/faq/run-execute-sh-shell-script/
    ```
If you already have ROS installed, copy the file mavros_install.sh into your home folder and run it instead.

### 3.3 Install QGroundControl for manual control of the simulated drone
    https://docs.qgroundcontrol.com/master/en/getting_started/download_and_install.html

### 3.4 Install the PX4 flight controller + Tools
1. Git clone from this folder
    ```
    https://github.com/PX4/PX4-Autopilot
    ```
2. In the terminal, go to the newly cloned folder and run the below command
    ```
    DONT_RUN=1 make px4_sitl_default gazebo
    ```
*In case of missing packages, go through the error msgs and install the missing packages. Repeat this step until you have all the required packages
3. After finishing all the steps above, run this command:
    ```
    source Tools/setup_gazebo.bash $(pwd) $(pwd)/build/px4_sitl_default
    ```
    
### 3.5 Set up development environment
1. Open up a new terminal 
2. In the new terminal run: 
    ```
    sudo gedit .bashrc
    ```
3. This will takes you to a new text file. In this text file, copy the lines below and paste them to the end of the file
    ```
    #environment variable
    export PX4_PATH="/home/<Your home folder here>/PX4-Autopilot"

    #PX4 sourcing
    export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$PX4_PATH
    export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:$PX4_PATH/Tools/sitl_gazebo
    ```
4. Save file and close the application

### 3.6 To launch the entire project:
    roslaunch bluejay_launch bluejay_sitl.launch 