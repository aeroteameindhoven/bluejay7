#ifndef ASTAR_H
#define ASTAR_H

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include "pathfinding.h"

class AStar : public pathfinding{
public:
    AStar(){}
    void calculatePath(costmap_2d::Costmap2D* costmap,
                       geometry_msgs::Point start, geometry_msgs::Point end,
                       std::vector<geometry_msgs::PoseStamped>& plan){
    }
};

#endif // ASTAR_H
