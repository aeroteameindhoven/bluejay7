#include "bluejay_taskmanager/landingclient.h"

landingClient::landingClient(){

}

landingClient::landingClient(bluejay_msgs::LandingGoal _goal){
    goal = _goal;
}

bool landingClient::executed(){
    ROS_INFO("LandingClient is active");
    actionlib::SimpleActionClient<bluejay_msgs::LandingAction> ac("landing_server", true);

    ROS_INFO("Waiting for landing action server to start.");
    ac.waitForServer(); //will wait for infinite time
    goal.LandingGoal_x = -1;
    goal.LandingGoal_y = -1;
    goal.LandingGoal_z = 0;

    ROS_INFO("Landing Action server started, sending goal.");
    ac.sendGoal(goal);
      // send a goal to the action

    bool finished_before_timeout_land = ac.waitForResult(ros::Duration(120.0));

    if (finished_before_timeout_land){
        actionlib::SimpleClientGoalState state_land = ac.getState();
        ROS_INFO("Landing Action finished: %s",state_land.toString().c_str());
        return true;
    }
    else {
        ROS_INFO("Landing Action did not finish before the time out.");
        return false;
    }
}

std::string landingClient::toString(){
    return "Landing Client";
}

void landingClient::addGoal(bluejay_msgs::LandingGoal _goal){
    goal = _goal;
}
