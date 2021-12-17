#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
//#include <bluejay_msgs/TakeOffAction.h>

//typedef actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> Client;

int main(int argc, char **argv)
{
  /*
    ros::init(argc, argv, "test_client");
    Client client("test_client", true); // true -> don't need ros::spin()??
    client.waitForServer();
    bluejay_msgs::TakeOffGoal goal;
    // Fill in goal here

    goal.altitudeGoal = 2;
    goal.velocityTakeoff = 0.5;

    client.sendGoal(goal);
    client.waitForResult(ros::Duration(5.0));
    if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Yay! test complete");*/
    return 0;
}
