#include "bluejay_taskmanager/task.h"

Task::Task(){

}

Task::Task(std::string _taskName, int _id, PRIORITY _priority){
    taskName = _taskName;
    id = _id;
    priority = _priority;
}

void Task::addAction(actionClient *client){
    allClients.push_back(client);
}

int Task::getID(){
    return id;
}

bool Task::executeTask(){
    ROS_INFO("task is being excuted");
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
