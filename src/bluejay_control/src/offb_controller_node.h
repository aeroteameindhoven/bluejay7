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
#include <bluejay_msgs/TakeOffAction.h>
#include <bluejay_msgs/NavigateAction.h>
#include <bluejay_msgs/LandingAction.h>
#include <dynamic_reconfigure/server.h>
#include <tf/transform_broadcaster.h>

class OffBControllerNode{
public:
    OffBControllerNode();
    void Init_Parameters();

private:
    ros::NodeHandle core;
    double current_time;
    double start_time;
    bool arm_before;
    bool navigate_CB_check;

    mavros_msgs::State current_state;
    mavros_msgs::SetMode set_mode;
    geometry_msgs::PoseStamped setPosition;
    mavros_msgs::CommandBool arm_cmd;
    geometry_msgs::Twist cmd_velo;
    geometry_msgs::TwistStamped px4_velo;

    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber vel_sub;
    ros::Subscriber takeoff_sub;
    ros::Subscriber navigate_sub;
    ros::Subscriber landing_sub;


    //publisher
    ros::Publisher local_pos_pub;
    ros::Publisher setpoint_velo_pub;

    //service
    ros::ServiceClient arming_client;
    ros::ServiceClient set_mode_client;

    void StateCallback(const mavros_msgs::State::ConstPtr& msg);
    void TakeOffCallback(const bluejay_msgs::TakeOffGoal::ConstPtr& msg);
    void NavigateCallback(const geometry_msgs::PoseStamped::ConstPtr& msg); //change the message type
    void LandingCallback(const bluejay_msgs::LandingGoal::ConstPtr& msg);
    void VelocityCallback(const geometry_msgs::Twist::ConstPtr& vel);
};

#endif // OFFB_CONTROLLER_NODE_H
