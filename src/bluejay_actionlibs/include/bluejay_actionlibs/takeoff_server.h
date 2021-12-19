#ifndef TAKEOFF_SERVER_H
#define TAKEOFF_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/TakeOffAction.h>

class TakeOffServer
{
protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<bluejay_msgs::TakeOffAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  bluejay_msgs::TakeOffFeedback feedback_;
  bluejay_msgs::TakeOffResult result_;

public:

  TakeOffServer(std::string name) :
    as_(nh_, name, boost::bind(&TakeOffServer::executeCB, this, _1), false),
    action_name_(name)
  {
    as_.start();
  }

  ~TakeOffServer(void)
   {
   }

  void executeCB(const bluejay_msgs::TakeOffGoalConstPtr &goal)
  {
    ROS_INFO("action is being executed");
    ros::Rate r(1);
    bool success = true;

    //do stuff here
    feedback_.altitude = 0;

    if(success)
    {
      feedback_.arm = true;

      while (feedback_.altitude <= goal->altitudeGoal){
      feedback_.altitude += 0.1;
      as_.publishFeedback(feedback_);
      r.sleep();
      }

      if (feedback_.altitude >= goal->altitudeGoal){
        result_.successTakeoff = true;
        ROS_INFO("TakeOff succeeded");
        //set action state to succeeded
        as_.setSucceeded(result_);
      }
    }
  }


};


#endif // TAKEOFF_SERVER_H
