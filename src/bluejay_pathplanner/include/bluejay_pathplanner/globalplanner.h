#ifndef GLOBALPLANNER_H
#define GLOBALPLANNER_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include "pathfinding.h"

class GlobalPlanner{
public:
    GlobalPlanner();
    void executeCB(geometry_msgs::PoseStamped::ConstPtr& msg);
private:
    ros::NodeHandle nh_;
    pathfinding *algorithm;
};

#endif // GLOBALPLANNER_H
