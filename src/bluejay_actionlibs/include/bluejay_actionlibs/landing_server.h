#ifndef LANDING_SERVER_H
#define LANDING_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/LandingAction.h>
#include <string>

class LandingServer
{
protected:
  ros::NodeHandle nh;
  //actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
//  TakeOffAction::FibonacciFeedback feedback_;
//  actionlib_tutorials::FibonacciResult result_;

public:



};

#endif // LANDING_SERVER_H
