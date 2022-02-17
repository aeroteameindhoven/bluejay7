#include "bluejay_taskmanager/moveclient.h"

moveClient::moveClient(){
    clientName = "Move";
    goal.MoveGoal_x = 3;
    goal.MoveGoal_y = 3;
    goal.MoveGoal_z = 0;
    delayTime = 1;
}

moveClient::moveClient(int _delayTime){
    clientName = "Move";
    delayTime = _delayTime;
    goal.MoveGoal_x = 3;
    goal.MoveGoal_y = 3;
    goal.MoveGoal_z = 0;
}

moveClient::moveClient(int _delayTime, bluejay_msgs::MoveGoal _goal){
    clientName = "Move";
    goal = _goal;
    delayTime = _delayTime;
}

bool moveClient::execute(){
    ros::Rate frequency(1);
    frequency.sleep();
    actionlib::SimpleActionClient<bluejay_msgs::MoveAction> ac("Move_server", true);
    ROS_INFO("Waiting for Move action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ac.sendGoal(goal); // send a goal to the action

    bool finished_before_timeout = ac.waitForResult(ros::Duration(180.0));

    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Move action finished: %s",state.toString().c_str());
        if(state == actionlib::SimpleClientGoalState::StateEnum::SUCCEEDED){
            return true;
        } else return false;
    } else {
        ROS_INFO("Move action did not finish before the time out.");
        return false;
    }
}

std::string moveClient::toString(){
    return "Move Client";
}
