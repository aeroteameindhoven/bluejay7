#ifndef TASKMANAGER_NODE_H
#define TASKMANAGER_NODE_H

#include <ros/ros.h>
#include <stack>
#include "takeoffclient.h"
#include "landingclient.h"
#include "task.h"

class TaskmanagerNode{
public:
    TaskmanagerNode();
private:
    ros::NodeHandle nh_;

    bool testsuccess1;
    bool testsuccess2;

    void InitParameter();
};

#endif // TASKMANAGER_NODE_H
