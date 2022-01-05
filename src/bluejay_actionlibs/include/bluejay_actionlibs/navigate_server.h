#ifndef NAVIGATE_SERVER_H
#define NAVIGATE_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/NavigateAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/Altitude.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>

class NavigateServer
{
private:
    uint64_t count;
    bool callback_Pose;
    bool callback_State;
    bool callback_path;
    ros::NodeHandle nh_;
    //actionlib::SimpleActionServer<bluejay_msgs::NavigateAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;
    // create messages that are used to published feedback/result
    bluejay_msgs::NavigateFeedback feedback_;
    bluejay_msgs::NavigateResult result_;
    mavros_msgs::State current_state;
    nav_msgs::Path global_path;
    geometry_msgs::PoseStamped local_goal;
    geometry_msgs::PoseStamped global_goal;

    //subscriber
    ros::Subscriber state_sub;
    ros::Subscriber pose_sub;
    ros::Subscriber path_sub;
    ros::Subscriber goal_sub;

    //publisher
    ros::Publisher local_pos_pub;
    ros::Publisher goal_pub;

    //service
    //ros::ServiceClient arming_client;
    void StateCallback(const mavros_msgs::State::ConstPtr& msg);
    void PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void GoalCallBack(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void PathCallBack(const nav_msgs::Path::ConstPtr& msg);
    void Init_Parameters();

public:
    NavigateServer();
    ~NavigateServer(void);
};


#endif // NAVIGATE_SERVER_H
