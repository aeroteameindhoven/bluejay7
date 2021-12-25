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

    //----------------------------------------------------------

    if (finished_before_timeout){
    actionlib::SimpleActionClient<bluejay_msgs::NavigateAction> ac_nav("navigate_server", true);

    ROS_INFO("Waiting for navigation action server to start.");
    ac_nav.waitForServer(); //will wait for infinite time
    goal_nav.set_pose_x = 3;
    goal_nav.set_pose_y = 3;
    goal_nav.set_pose_z = 3;

    ROS_INFO("Nav Action server started");
    ac_nav.sendGoal(goal_nav);

    ROS_INFO("Nav Action server started, sending goal.");
      // send a goal to the action

      bool finished_before_timeout_nav = ac_nav.waitForResult(ros::Duration(120.0));

      if (finished_before_timeout_nav){
        actionlib::SimpleClientGoalState state_nav = ac_nav.getState();
        ROS_INFO("Nav Action finished: %s",state_nav.toString().c_str());
        }
      else
        ROS_INFO("Nav Action did not finish before the time out.");

    //-----------------------------------------------------------------------
    if (finished_before_timeout_nav){
    actionlib::SimpleActionClient<bluejay_msgs::LandingAction> ac_land("landing_server", true);

    ROS_INFO("Waiting for landing action server to start.");
    ac_land.waitForServer(); //will wait for infinite time
    goal_land.LandingGoal_x = -1;
    goal_land.LandingGoal_y = -1;
    goal_land.LandingGoal_z = 0;

    ROS_INFO("land Action server started");
    ac_land.sendGoal(goal_land);

    ROS_INFO("land Action server started, sending goal.");
      // send a goal to the action

      bool finished_before_timeout_land = ac_land.waitForResult(ros::Duration(120.0));

      if (finished_before_timeout_land){
        actionlib::SimpleClientGoalState state_land = ac_land.getState();
        ROS_INFO("land Action finished: %s",state_land.toString().c_str());
        }
      else
        ROS_INFO("land Action did not finish before the time out.");
      }
}
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "taskmanager_node");
    TakeOffClient();
    ros::spin();
    return 0;
}
