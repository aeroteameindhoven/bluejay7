#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <bluejay_msgs/TakeOffAction.h>

class TakeOffClient{
private:
  bool callback_Pose;

  ros::NodeHandle nh_;
  geometry_msgs::PoseStamped pose_sub;
  bluejay_msgs::TakeOffGoal goal;

public:
  TakeOffClient();
  void PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
};

#endif // TASKMANAGER_H
