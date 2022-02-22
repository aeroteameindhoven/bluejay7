#include "bluejay_taskmanager/circleclient.h"
circleClient::circleClient(){
    clientName = "circle";
    goal.CircleGoal_num = 3.0;
    delayTime = 1;
}

circleClient::circleClient(int _delayTime){
    clientName = "circle";
    delayTime = _delayTime;
    goal.CircleGoal_num = 3.0;
}

circleClient::circleClient(int _delayTime, bluejay_msgs::CircleGoal _goal){
    clientName = "circle";
    goal = _goal;
    delayTime = _delayTime;
}


bool circleClient::execute(){
    ros::Rate frequency(1);
    frequency.sleep();
    actionlib::SimpleActionClient<bluejay_msgs::CircleAction> ac("circle_server", true);
    ROS_INFO("Waiting for circle action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ac.sendGoal(goal); // send a goal to the action
    ROS_INFO("Sending goal to circle action server.");
    bool finished_before_timeout = ac.waitForResult(ros::Duration(180.0));

    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("circle action finished: %s",state.toString().c_str());
        if(state == actionlib::SimpleClientGoalState::StateEnum::SUCCEEDED){
            return true;
        } else return false;
    } else {
        ROS_INFO("circle action did not finish before the time out.");
        return false;
    }
}

std::string circleClient::toString(){
    return "circle Client";
}

