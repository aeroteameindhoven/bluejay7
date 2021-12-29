#include "bluejay_taskmanager/takeoffclient.h"

takeoffClient::takeoffClient(){
    clientName = "takeoff";
    goal.TakeoffGoal_x = -1.0;
    goal.TakeoffGoal_y = -1.0;
    goal.TakeoffGoal_z = 2;
    delayTime = 1;
}

takeoffClient::takeoffClient(int _delayTime){
    clientName = "takeoff";
    delayTime = _delayTime;
    goal.TakeoffGoal_x = -1.0;
    goal.TakeoffGoal_y = -1.0;
    goal.TakeoffGoal_z = 2;
}

takeoffClient::takeoffClient(int _delayTime, bluejay_msgs::TakeOffGoal _goal){
    clientName = "takeoff";
    goal = _goal;
    delayTime = _delayTime;
}

bool takeoffClient::execute(){
    ros::Rate frequency(1);
    frequency.sleep();
    actionlib::SimpleActionClient<bluejay_msgs::TakeOffAction> ac("takeoff_server", true);
    ROS_INFO("Waiting for TakeOff action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ac.sendGoal(goal); // send a goal to the action

    bool finished_before_timeout = ac.waitForResult(ros::Duration(120.0));

    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("TakeOff action finished: %s",state.toString().c_str());
        if(state == actionlib::SimpleClientGoalState::StateEnum::SUCCEEDED){
            return true;
        } else return false;
    } else {
        ROS_INFO("TakeOff action did not finish before the time out.");
        return false;
    }
}

std::string takeoffClient::toString(){
    return "TakeOff Client";
}
