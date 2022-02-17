#include "bluejay_taskmanager/taskmanager_node.h"
#include "bluejay_taskmanager/takeoffclient.h"
#include "bluejay_taskmanager/landingclient.h"
#include "bluejay_taskmanager/fakeclient.h"
#include "bluejay_taskmanager/moveclient.h"

TaskmanagerNode::TaskmanagerNode(){
    Task test;
    Task printTest;
    takeoffClient *_fakeClient = new takeoffClient();
    landingClient *_fakeClient2 = new landingClient();
    moveClient *_moveClient = new moveClient();

    test.addAction(_fakeClient);
    test.addAction(_moveClient);
    test.addAction(_fakeClient2);

    addTask(test);
	
    while (ros::ok()) {
        if (!allTask.empty()){
            pool.submit(allTask.front());
            allTask.erase(allTask.begin());
        }
    }
}

void TaskmanagerNode::addTask(Task task){
    allTask.push_back(task);
}

int main (int argc, char **argv){
    ros::init(argc, argv, "taskmanager_node");
    TaskmanagerNode TaskmanagerNode;
    ros::spin();
    return 0;
}
