#ifndef TEST_FAKE_POSE
#define TEST_FAKE_POSE

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/Altitude.h>
#include <ros/ros.h>
//#include <tf/transform_broadcaster.h>

class test_fake_pose {
 public:
  test_fake_pose();

 private:
  ros::NodeHandle core;

  // Subscribers
  ros::Subscriber mavros_odom_sub;
  ros::Subscriber mavros_altitude_sub;
  // Publishers
  ros::Publisher mavros_odom_pub;
  ros::Publisher mocap_pose_pub;
  //tf::TransformBroadcaster odom_broadcaster;
  
  nav_msgs::Odometry odom_out;
  geometry_msgs::PoseStamped mocap;
  
  //Callback functions
  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);
  void altitudeCallback(const mavros_msgs::Altitude::ConstPtr& msg);
  ros::Time current_time;
};
#endif  // PX4_REALSENSE_BRIDGE

