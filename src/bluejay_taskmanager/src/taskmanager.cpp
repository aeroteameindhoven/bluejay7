#include "taskmanager.h"

TakeOffClient::TakeOffClient(){
  ROS_INFO("TakeOffClient is active");
  callback_Pose = false;

  //create a subscriber to the position
  ros::Subscriber pose_sub = nh_.subscribe<geometry_msgs::PoseStamped>
      ("/mavros/local_pose", 10, &TakeOffClient::PoseCallback, this);

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> ac("takeoff_server", true);

  ROS_INFO("Waiting for action server to start.");
  ac.waitForServer(); //will wait for infinite time
  //while (!callback_Pose);
  goal.TakeoffGoal_x = 0;
  goal.TakeoffGoal_y = 0;
  goal.TakeoffGoal_z = 1.5;
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

void TakeOffClient::PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
  ROS_INFO_ONCE("TakeOff_Client received the first position.");

  goal.TakeoffGoal_x = msg->pose.position.x;
  goal.TakeoffGoal_y = msg->pose.position.y;
  goal.TakeoffGoal_z = 1.5;
  callback_Pose = true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "offboard_node");
    TakeOffClient();
    ros::spin();
    return 0;
}
