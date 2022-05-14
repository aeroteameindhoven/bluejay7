#ifndef GLOBALPLANNER_H
#define GLOBALPLANNER_H

#include <tf/transform_listener.h>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include "astar.h"
#include "rrts.h"

enum algorithm { ASTAR, RRT, DSTAR };

class GlobalPlanner{
public:
    GlobalPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros, algorithm algo);

    ~GlobalPlanner();

    void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    bool makePlan(const geometry_msgs::PoseStamped& start,
                  const geometry_msgs::PoseStamped& goal,
                  std::vector<geometry_msgs::PoseStamped>& plan
                 );
private:
    ros::NodeHandle nh_;
    pathfinding *pathfinder;

    costmap_2d::Costmap2DROS* costmap_ros;
    costmap_2d::Costmap2D* costmap;

    std::string name;
    std::string frame_id_;
    ros::Publisher plan_pub_;
    bool initialized_, allow_unknown_;

    ros::Subscriber costMap_sub;
    ros::Subscriber position_sub;
    ros::Subscriber destination_sub;

    double planner_window_x_, planner_window_y_, default_tolerance_;
    boost::mutex mutex_;

    void calculatePath(costmap_2d::Costmap2D* costmap,
                       geometry_msgs::Point start, geometry_msgs::Point end);

    void mapToWorld(double mx, double my, double& wx, double& wy);
    bool worldToMap(double wx, double wy, double& mx, double& my);
    void clearRobotCell(const geometry_msgs::PoseStamped& global_pose, unsigned int mx, unsigned int my);
};

#endif // GLOBALPLANNER_H
