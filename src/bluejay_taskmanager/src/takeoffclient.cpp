#include "bluejay_taskmanager/takeoffclient.h"

takeoffClient::takeoffClient(){

}

bool takeoffClient::executed(){
    ROS_INFO("take off is being excuted");
    return true;
}

std::string takeoffClient::toString(){
    return "take off client";
}
