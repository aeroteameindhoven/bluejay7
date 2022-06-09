#ifndef VISION_H
#define VISION_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Path.h>
#include <sensor_msgs/Image.h>

class ArucoNode{
public:
	ArucoNode();
	
private:
	ros::NodeHandle core;
	
	ros::Subscriber camera_info_sub;
    ros::Subscriber image_sub;
    ros::Subscriber parameter_descriptions_sub;
    ros::Subscriber parameter_updates_sub;
    
    ros::Publisher position_pub;
    
    void imageCallback(const sensor_msgs::Image::ConstPtr& msg);
};

#endif // VISION_H
