#ifndef LANDING_SERVER_H
#define LANDING_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/LandingAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <queue>

class LandingServer
{
private:
    bool callback_Pose;
    bool callback_State;
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<bluejay_msgs::LandingAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    // create messages that are used to published feedback/result
    bluejay_msgs::LandingFeedback feedback_;
    bluejay_msgs::LandingResult result_;
    mavros_msgs::State current_state;
    geometry_msgs::Pose current_pose;
    geometry_msgs::Pose landing_pose;
    geometry_msgs::Pose vision_pose;

    std::queue<geometry_msgs::Pose> qr_poses;

    bluejay_msgs::LandingGoal landing_goal;
    geometry_msgs::PoseStamped global_goal;


    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber pose_sub;
    ros::Subscriber vision_sub;

    //publisher
    ros::Publisher local_pos_pub;
    ros::Publisher goal_pub;
    ros::Publisher pose_pub;

    //service
    //ros::ServiceClient arming_client;
    void StateCallback(const mavros_msgs::State::ConstPtr& msg);
    void PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void VisionCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void Init_Parameters();

public:
    LandingServer(std::string name);
    ~LandingServer();

    void executeCB(const bluejay_msgs::LandingGoalConstPtr &goal);

};

#endif // LANDING_SERVER_H
