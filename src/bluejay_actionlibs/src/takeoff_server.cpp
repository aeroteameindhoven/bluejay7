#include "bluejay_actionlibs/takeoff_server.h"

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

    ros::init(argc, argv, "takeoff_server");
    //TakeOffServer::as_(nh_, "takeoff_server", boost::bind(&TakeOffServer::executeCB, _1, &TakeOffServer::as_), false);
    //TakeOffServer::as_.start();
    TakeOffServer takeoff_server("takeoff_server");
    ros::spin();

    return 0;
}
