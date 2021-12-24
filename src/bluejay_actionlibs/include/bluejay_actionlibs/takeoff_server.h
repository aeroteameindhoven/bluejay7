#ifndef TAKEOFF_SERVER_H
#define TAKEOFF_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/TakeOffAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/Altitude.h>

class TakeOffServer
{
protected:
  bool callback_Pose;
  bool callback_State;
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<bluejay_msgs::TakeOffAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  bluejay_msgs::TakeOffFeedback feedback_;
  bluejay_msgs::TakeOffResult result_;
  mavros_msgs::State current_state;
  geometry_msgs::Pose takeoff_pose;

  //subscriber
  ros::Subscriber state_sub;
  ros::Subscriber altitude_sub;

  //publisher
  ros::Publisher local_pos_pub;

  //service
  //ros::ServiceClient arming_client;
  void StateCallback(const mavros_msgs::State::ConstPtr& msg);
  void PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void Init_Parameters();

public:
  TakeOffServer(std::string name);
  ~TakeOffServer(void);

  void executeCB(const bluejay_msgs::TakeOffGoalConstPtr &goal);

};


#endif // TAKEOFF_SERVER_H
