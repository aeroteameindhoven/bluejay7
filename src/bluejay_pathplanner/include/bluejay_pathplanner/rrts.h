#ifndef RRTS_H
#define RRTS_H

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include "pathfinding.h"

class RRT : public pathfinding{
public:
    RRT();
    void calculatePath(costmap_2d::Costmap2D* costmap,
                       geometry_msgs::Point start, geometry_msgs::Point end,
                       std::vector<geometry_msgs::PoseStamped>& plan);
};
#endif // RRTS_H
