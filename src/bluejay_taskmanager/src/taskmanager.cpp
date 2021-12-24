#include "taskmanager.h"

TakeOffClient::TakeOffClient(){
  ROS_INFO("TakeOffClient is active");

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> ac("takeoff_server", true);

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer(); //will wait for infinite time
  goal.TakeoffGoal_x = -1.0;
  goal.TakeoffGoal_y = -1.0;
  goal.TakeoffGoal_z = 3;

  ROS_INFO("Action server started");
  ac.sendGoal(goal);

  ROS_INFO("Action server started, sending goal.");
    // send a goal to the action

    bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0));

    if (finished_before_timeout){
      actionlib::SimpleClientGoalState state = ac.getState();
      ROS_INFO("Action finished: %s",state.toString().c_str());
      }
    else
      ROS_INFO("Action did not finish before the time out.");

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    TakeOffClient();
    ros::spin();
    return 0;
}
