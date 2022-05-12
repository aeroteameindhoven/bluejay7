#include "bluejay_pathplanner/globalplanner.h"

GlobalPlanner::GlobalPlanner(std::string _name, costmap_2d::Costmap2DROS* _costmap_ros){
    name = _name;
    costmap_ros = _costmap_ros;
    unsigned int cx = costmap_ros->getCostmap()->getSizeInCellsX();
    unsigned int cy = costmap_ros->getCostmap()->getSizeInCellsX();
    ROS_INFO("cx = %d, cy = %d", cx, cy);
}

GlobalPlanner::~GlobalPlanner(){

}
