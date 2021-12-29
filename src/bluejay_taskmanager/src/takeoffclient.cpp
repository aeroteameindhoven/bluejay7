#include "bluejay_taskmanager/takeoffclient.h"

takeoffClient::takeoffClient(){
}

bool takeoffClient::executed(){
    ROS_INFO("TakeOffClient is active.");

    // create the action client
    // true causes the client to spin its own thread
    actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> ac("takeoff_server", true);

    ROS_INFO("Waiting for TakeOff action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ROS_INFO("TakeOff action server started, sending goal.");
    goal.TakeoffGoal_x = -1.0;
    goal.TakeoffGoal_y = -1.0;
    goal.TakeoffGoal_z = 0;

    ac.sendGoal(goal); // send a goal to the action

    bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0));

      if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("TakeOff action finished: %s",state.toString().c_str());
        return true;
        }
      else {
        ROS_INFO("TakeOff action did not finish before the time out.");
        return false;
      }
}

std::string takeoffClient::toString(){
    return "TakeOff Client";
}
