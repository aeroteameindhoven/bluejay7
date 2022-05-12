#ifndef MOVE_SERVER_H
#define MOVE_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/MoveAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>


class MoveServer
{
private:
    bool callback_Pose;
    bool callback_State;
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<bluejay_msgs::MoveAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;
    // create messages that are used to published feedback/result
    bluejay_msgs::MoveFeedback feedback_;
    bluejay_msgs::MoveResult result_;
    mavros_msgs::State current_state;
    geometry_msgs::Pose Move_pose;
    geometry_msgs::Pose Initial_pose;
    bluejay_msgs::MoveGoal Move_goal;
    geometry_msgs::PoseStamped global_goal;


    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber pose_sub;

    //publisher
    ros::Publisher local_pos_pub;
    ros::Publisher goal_pub;

    //service
    //ros::ServiceClient arming_client;
    void StateCallback(const mavros_msgs::State::ConstPtr& msg);
    void PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void Init_Parameters();

public:
    MoveServer(std::string name);
    ~MoveServer();

    void executeCB(const bluejay_msgs::MoveGoalConstPtr &goal);

};

#endif // Move_SERVER_H
