#ifndef CIRCLE_SERVER_H
#define CIRCLE_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/CircleAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>


class CircleServer
{
protected:
  bool success;
  bool callback_Pose;
  bool callback_State;
  float radius;
  float cx;
  float cy;
  double theta = 0.0;
  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<bluejay_msgs::CircleAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;

  // create messages that are used to published feedback/result
  bluejay_msgs::CircleFeedback feedback_;
  bluejay_msgs::CircleResult result_;
  mavros_msgs::State current_state;
  geometry_msgs::Pose Circle_pose;
  geometry_msgs::Pose Circle_goal;
  //bluejay_msgs::CircleGoal number_of_circles;

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
  CircleServer(std::string name);
  ~CircleServer(void);

  void executeCB(const bluejay_msgs::CircleGoalConstPtr &goal);

};


#endif // CIRCLE_SERVER_H
