#include "bluejay_taskmanager/taskmanager_node.h"


TaskmanagerNode::TaskmanagerNode(){
    InitParameter();
    Task test;
    takeoffClient *fakeClient = new takeoffClient();
    landingClient *fakeClient2 = new landingClient();
    testsuccess1 = test.addAction(fakeClient);
    testsuccess2 = test.addAction(fakeClient2);

    while (!testsuccess1 & !testsuccess2);
    test.executeTask();
}

void TaskmanagerNode::InitParameter(){
    testsuccess1 = false;
    testsuccess2 = false;
}

int main (int argc, char **argv){
    ros::init(argc, argv, "taskmanager_node");
    TaskmanagerNode TaskmanagerNode;
    ros::spin();
    return 0;
}
