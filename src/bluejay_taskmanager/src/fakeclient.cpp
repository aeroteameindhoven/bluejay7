#include "bluejay_taskmanager/fakeclient.h"

fakeClient::fakeClient(){
};

fakeClient::fakeClient(std::string _message){
    ROS_INFO("fake client created");
    message = _message;
};

bool fakeClient::execute(){
    while (ros::ok()){
        ROS_INFO("%s: mock task is being executed", message.c_str());
        ros::Duration(10).sleep();
    }
    return true;
}

std::string fakeClient::toString(){
    return "smd";
};

void fakeClient::addGoal(){

};


