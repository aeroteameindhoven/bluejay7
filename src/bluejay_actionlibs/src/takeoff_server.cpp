#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <bluejay_msgs/TakeOffAction.h>

//typedef actionlib::SimpleActionServer<bluejay_msgs::TakeOffAction> Server;

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

/*
void execute(const bluejay_msgs::TakeOffGoalConstPtr& goal, Server* as)
{
    ROS_INFO("action is being executed");
    //do sth here

    //
}*/

int main(int argc, char** argv)
{
  /*
    ros::init(argc, argv, "takeoff_server");
    ros::NodeHandle n;
    Server server(n, "take_off", boost::bind(&execute, _1, &server), false);
    server.start();
    ros::spin();
    */
    return 0;
}
