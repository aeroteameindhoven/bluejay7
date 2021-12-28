#ifndef TASKMANAGER_NODE_H
#define TASKMANAGER_NODE_H

#include <ros/ros.h>
#include <stack>
#include "takeoffclient.h"

class TaskmanagerNode{
public:
    TaskmanagerNode();

private:
    ros::NodeHandle nh_;
};

#endif // TASKMANAGER_NODE_H
