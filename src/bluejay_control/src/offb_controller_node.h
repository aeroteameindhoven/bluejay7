#ifndef OFFB_CONTROLLER_NODE_H
#define OFFB_CONTROLLER_NODE_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Path.h>

#include <bluejay_control/ControlConfig.h>
#include <dynamic_reconfigure/server.h>

class OffBControllerNode{
public:
    OffBControllerNode();
    void Init_Parameters();

private:
    ros::NodeHandle core;
    double current_time;
    double start_time;
    bool check_callback;
    bool check_goal;
    int count;

    nav_msgs::Path global_path;
    mavros_msgs::State current_state;
    geometry_msgs::Twist cmd_velo;
    geometry_msgs::TwistStamped px4_velo;
    mavros_msgs::SetMode offb_set_mode;
    geometry_msgs::PoseStamped pose;
    geometry_msgs::PoseStamped global_goal;
    mavros_msgs::CommandBool arm_cmd;

    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber vel_sub;

    //publisher
    ros::Publisher local_pos_pub;
    ros::Publisher setpoint_velo_pub;

    //service
    dynamic_reconfigure::Server<bluejay_control::ControlConfig> server;
    dynamic_reconfigure::Server<bluejay_control::ControlConfig>::CallbackType f;
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;

    void DynamicCallback(bluejay_control::ControlConfig &config, uint32_t level);
    void GoalCallBack(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void PathCallBack(const nav_msgs::Path::ConstPtr& msg);
    void StateCallback(const mavros_msgs::State::ConstPtr& msg);
    void VelocityCallback(const geometry_msgs::Twist::ConstPtr& vel);
};

#endif // OFFB_CONTROLLER_NODE_H
