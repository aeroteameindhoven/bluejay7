#ifndef NAVIGATION_SERVER_H
#define NAVIGATION_SERVER_H

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/MoveAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <tf/transform_listener.h>
#include "bluejay_pathplanner/globalplanner.h"

class NavigationServer
{
public:
    /**
     * @brief  Constructor for the actions
     * @param name The name of the action
     * @param tf A reference to a TransformListener
     */
    NavigationServer(std::string name, tf2_ros::Buffer& tf);

    /**
     * @brief  Destructor - Cleans up
     */
    ~NavigationServer();

    /**
     * @brief  Performs a control cycle
     * @param goal A reference to the goal to pursue
     * @return True if processing of the goal is done, false otherwise
     */
    bool executeCycle(geometry_msgs::PoseStamped& goal);

private:
    double controller_freq;
    double planner_frequency;

    bool callback_State;
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<bluejay_msgs::MoveAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
    std::string action_name_;

    costmap_2d::Costmap2DROS* global_planner_costmap_ros_;
    costmap_2d::Costmap2DROS* local_planner_costmap_ros_;

    GlobalPlanner* Gplanner;

    std::string frame_id_;
    ros::Publisher plan_pub_;
    bool initialized_, allow_unknown_;

    /**
     * @brief  Performs action when received goal
     * @param goal A reference to the goal to pursue
     */
    void executeCB(const bluejay_msgs::MoveGoalConstPtr &goal);
};


#endif // NAVIGATION_SERVER_H
