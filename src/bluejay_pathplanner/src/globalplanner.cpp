#include "bluejay_pathplanner/globalplanner.h"

GlobalPlanner::GlobalPlanner(std::string _name, costmap_2d::Costmap2DROS* _costmap_ros,
                             enum algorithm algo){
    name = _name;
    costmap_ros = _costmap_ros;
    costmap = costmap_ros->getCostmap();
    unsigned int cx = costmap->getSizeInCellsX();
    unsigned int cy = costmap->getSizeInCellsX();
    ROS_INFO("cx = %d, cy = %d", cx, cy);

    double resolut = costmap->getResolution();
    ROS_INFO("resolut = %f", resolut);

    if (algo == ASTAR){
        pathfinder = new AStar();
    }
}

GlobalPlanner::~GlobalPlanner(){

}

bool GlobalPlanner::makePlan(const geometry_msgs::PoseStamped& start,
              const geometry_msgs::PoseStamped& goal,
              std::vector<geometry_msgs::PoseStamped>& plan){
    pathfinder->calculatePath(costmap, start.pose.position, goal.pose.position, plan);
    if (plan.size() == 0) return false;
    return true;
}
