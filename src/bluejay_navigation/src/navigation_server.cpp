#include "bluejay_navigation/navigation_server.h"

/*navigate action server(s) communicate with
 * offboard controller through ROS Master
          ------------------------
          --    Task Manager    --
          ------------------------
                    |  |
          ------------------------
          --    Action server   --
          ------------------------
                    |  |
          ------------------------
          --    off_b control   --
          ------------------------
*/
NavigationServer::NavigationServer(std::string name, tf2_ros::Buffer& tf) :
    as_(nh_, name, boost::bind(&NavigationServer::executeCB, this, _1), false),
    action_name_(name)
{
    global_planner_costmap_ros_ = new costmap_2d::Costmap2DROS("global_costmap", tf);
    Gplanner = new GlobalPlanner("global_costmap",global_planner_costmap_ros_);

    global_planner_costmap_ros_->start();
}

void NavigationServer::executeCB(const bluejay_msgs::MoveGoalConstPtr &goal){
    //Gplanner->makePlan(goal->)

}

bool NavigationServer::executeCycle(geometry_msgs::PoseStamped& goal){
    return true;
}

NavigationServer::~NavigationServer(){
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "NavigationServer");
    tf2_ros::Buffer buffer(ros::Duration(10));
    tf2_ros::TransformListener tf(buffer);

    NavigationServer NavigationServer("Navigation_server", buffer);
    ros::spin();
    return 0;
}
