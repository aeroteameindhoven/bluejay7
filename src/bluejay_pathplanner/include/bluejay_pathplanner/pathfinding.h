#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <costmap_2d/costmap_2d_ros.h>

class pathfinding{
public:
    virtual ~pathfinding(){}
    virtual void calculatePath(costmap_2d::Costmap2D* costmap,
                     geometry_msgs::Point start, geometry_msgs::Point end,
                     std::vector<geometry_msgs::PoseStamped>& plan) = 0;
};
#endif // PATHFINDING_H
