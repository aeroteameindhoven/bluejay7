#include <ros/ros.h>
#include <bluejay_msgs/TakeOffAction.h>
#include <actionlib/server/simple_action_server.h>

typedef actionlib::SimpleActionServer<bluejay_msgs::TakeOffAction> Server;

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

void execute(const bluejay_msgs::TakeOffGoalConstPtr& goal, Server* as)
{
    ROS_INFO("action is being executed");
    //do sth here

    //
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "takeoff_server is up");
    ros::NodeHandle n;
    ros::spin();
    return 0;
}
