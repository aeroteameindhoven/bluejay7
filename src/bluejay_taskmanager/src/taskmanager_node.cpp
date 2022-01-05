#include "bluejay_taskmanager/taskmanager_node.h"

TaskmanagerNode::TaskmanagerNode(){
    Task test;
    Task printTest;
    takeoffClient *_fakeClient = new takeoffClient();
    landingClient *_fakeClient2 = new landingClient();
    fakeClient *_fakeClient3 = new fakeClient("Michem");

    test.addAction(_fakeClient);
    test.addAction(_fakeClient2);
    printTest.addAction(_fakeClient3);

    while (ros::ok()) {
        if (!allTask.empty()){
            pool.submit(allTask.front());
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
