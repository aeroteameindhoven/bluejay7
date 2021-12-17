#ifndef TAKEOFF_SERVER_H
#define TAKEOFF_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/TakeOffAction.h>

class TakeOffServer
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<actionlib_tutorials::FibonacciAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
//  TakeOffAction::FibonacciFeedback feedback_;
//  actionlib_tutorials::FibonacciResult result_;

public:

  TakeOffServer(std::string name) :
    as_(nh_, name, boost::bind(&TakeOffServer::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  void executeCB(const TakeOffAction::TakeOffGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;

    //do stuff here

    if(success)
    {
    }
  }


};


#endif // TAKEOFF_SERVER_H
