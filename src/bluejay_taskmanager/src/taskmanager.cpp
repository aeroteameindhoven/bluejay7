#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <bluejay_msgs/TakeOffAction.h>

//typedef actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> Client;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_client");
    // create the action client
      // true causes the client to spin its own thread
    actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> ac("takeoff_server", true);

      ROS_INFO("Waiting for action server to start.");
      // wait for the action server to start
      ac.waitForServer(); //will wait for infinite time

      ROS_INFO("Action server started, sending goal.");
      // send a goal to the action
      bluejay_msgs::TakeOffGoal goal;
      goal.altitudeGoal = 1;
      ac.sendGoal(goal);
      ROS_INFO("Goal sent");


    /*Client client("test_client", true); // true -> don't need ros::spin()??
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
