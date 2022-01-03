#ifndef TASKMANAGER_NODE_H
#define TASKMANAGER_NODE_H

#include <ros/ros.h>
#include <vector>
#include "takeoffclient.h"
#include "landingclient.h"
#include "fakeclient.h"
#include "task.h"
#include "bluejay_taskmanager/threadpool.h"


class TaskmanagerNode{
public:
    TaskmanagerNode();
    void addTask(Task task);
    void cancelTask();
private:
    std::vector<Task> allTask;
    ros::NodeHandle nh_;
};

#endif // TASKMANAGER_NODE_H
