#include "bluejay_taskmanager/task.h"

Task::Task(){

}

bool Task::addAction(actionClient *client){
    allClients.push_back(client);
    return true;
}

bool Task::executeTask(){
    for (const auto& value : allClients){
        bool isActionCompleted = value->executed();
        if (!isActionCompleted){
            ROS_INFO("%s could not complete.", value->toString().c_str());
            return false;
        }
        ROS_INFO("%s completed.", value->toString().c_str());
    }
    return true;
}
