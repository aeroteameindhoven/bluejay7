#include "bluejay_taskmanager/taskmanager_node.h"

TaskmanagerNode::TaskmanagerNode(){
    Task test;
    takeoffClient *fakeClient = new takeoffClient();
    //landingClient *fakeClient2 = new landingClient();
    //takeoffClient *fakeClient3 = new takeoffClient(10);
    test.addAction(fakeClient);
    //test.addAction(fakeClient2);
    //test.addAction(fakeClient3);
    test.executeTask();
}

int main (int argc, char **argv){
    ros::init(argc, argv, "taskmanager_node");
    TaskmanagerNode TaskmanagerNode;
    ros::spin();
    return 0;
}
