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
#include <bluejay_msgs/MoveAction.h>
#include <bluejay_msgs/CircleAction.h>

/**
 * @class OffBControllerNode
 * @brief A class that process waypoint from navigation group server that moves the drone base to a goal location.
 */
class OffBControllerNode{
public:
    OffBControllerNode();
    void Init_Parameters();

private:
    ros::NodeHandle core;
    std::string mode_before;

    mavros_msgs::State current_state;
    mavros_msgs::SetMode set_mode;
    geometry_msgs::PoseStamped setPosition;
    mavros_msgs::CommandBool arm_cmd;
    geometry_msgs::Twist cmd_velo;

    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber vel_sub;
    ros::Subscriber takeoff_sub;
    ros::Subscriber navigate_sub;
    ros::Subscriber landing_sub;
    ros::Subscriber move_sub;
    ros::Subscriber circle_sub;

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
    void MoveCallback(const bluejay_msgs::MoveGoal::ConstPtr& msg);
    void VelocityCallback(const geometry_msgs::Twist::ConstPtr& vel);
    void CircleCallback(const geometry_msgs::Pose::ConstPtr& msg);
};

#endif // OFFB_CONTROLLER_NODE_H
