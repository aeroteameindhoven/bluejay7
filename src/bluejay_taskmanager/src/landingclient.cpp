#include "bluejay_taskmanager/landingclient.h"

landingClient::landingClient(){

}

landingClient::landingClient(bluejay_msgs::LandingGoal _goal){
    goal = _goal;
}

bool landingClient::executed(){
    ROS_INFO("landing is being excuted");
    return true;
}

std::string landingClient::toString(){
    return "landing client";
}

void landingClient::addGoal(bluejay_msgs::LandingGoal _goal){
    goal = _goal;
}
