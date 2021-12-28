#include "bluejay_taskmanager/task.h"

Task::Task(){

}

void Task::addAction(actionClient *client){
    allClients.push_back(client);
}

bool Task::executeTask(){
    for (const auto& value : allClients){
        bool isActionCompleted = value->executed();
        if (!isActionCompleted){
            return false;
        }
    }
}
