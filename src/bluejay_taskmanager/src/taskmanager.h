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

  ros::NodeHandle nh_;
  bluejay_msgs::TakeOffGoal goal;

public:
  TakeOffClient();
};

#endif // TASKMANAGER_H
