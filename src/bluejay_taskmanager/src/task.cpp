#include "bluejay_taskmanager/task.h"

Task::Task(){

}

void Task::addAction(actionClient *client){
    allClients.push_back(client);
}

bool Task::executeTask(){
    for (const auto& value : allClients){
        bool isActionCompleted = value->execute();
        if (!isActionCompleted){
            ROS_INFO("%s could not complete.", value->toString().c_str());
            return false;
        }
        ROS_INFO("%s completed.", value->toString().c_str());
    }
    return true;
}
