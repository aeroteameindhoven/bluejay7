#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <bluejay_msgs/TakeOffAction.h>
#include <bluejay_msgs/NavigateAction.h>
#include <bluejay_msgs/LandingAction.h>

class TakeOffClient{
private:

  ros::NodeHandle nh_;
  bluejay_msgs::TakeOffGoal goal;
  bluejay_msgs::NavigateGoal goal_nav;
  bluejay_msgs::LandingGoal goal_land;

public:
  TakeOffClient();
};

#endif // TASKMANAGER_H

