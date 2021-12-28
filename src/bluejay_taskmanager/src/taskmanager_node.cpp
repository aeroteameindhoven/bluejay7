#include "bluejay_taskmanager/taskmanager_node.h"


TaskmanagerNode::TaskmanagerNode(){

}

int main (int argc, char **argv){
    ros::init(argc, argv, "taskmanager_node");

    Task test;
    takeoffClient *fakeClient = new takeoffClient();
    landingClient *fakeClient2 = new landingClient();
    test.addAction(fakeClient);
    test.addAction(fakeClient2);

    test.executeTask();
    ros::spin();
    return 0;
}
