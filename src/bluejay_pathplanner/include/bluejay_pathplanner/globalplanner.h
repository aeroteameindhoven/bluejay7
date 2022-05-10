#ifndef GLOBALPLANNER_H
#define GLOBALPLANNER_H

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <tf/transform_listener.h>
#include "pathfinding.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>

///costmap_node/costmap/costmap

class GlobalPlanner{
public:
    GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    ~GlobalPlanner();

    void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    bool makePlan(const geometry_msgs::PoseStamped& start,
                  const geometry_msgs::PoseStamped& goal,
                  std::vector<geometry_msgs::PoseStamped>& plan
                 );
private:
    ros::NodeHandle nh_;
    pathfinding *algorithm;

    //tf2_ros::Buffer& tf_;
    costmap_2d::Costmap2DROS* costmap_ros;
    std::string name;
    std::string frame_id_;
    ros::Publisher plan_pub_;
    bool initialized_, allow_unknown_;

    ros::Subscriber costMap_sub;
    ros::Subscriber position_sub;
    ros::Subscriber destination_sub;

    double planner_window_x_, planner_window_y_, default_tolerance_;
    boost::mutex mutex_;

    void mapToWorld(double mx, double my, double& wx, double& wy);
    bool worldToMap(double wx, double wy, double& mx, double& my);
    void clearRobotCell(const geometry_msgs::PoseStamped& global_pose, unsigned int mx, unsigned int my);
};

#endif // GLOBALPLANNER_H
