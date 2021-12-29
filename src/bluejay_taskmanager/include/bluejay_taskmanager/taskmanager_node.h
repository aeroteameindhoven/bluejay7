#ifndef TASKMANAGER_NODE_H
#define TASKMANAGER_NODE_H

#include <ros/ros.h>
#include <vector>
#include "takeoffclient.h"
#include "landingclient.h"
#include "task.h"

class TaskmanagerNode{
public:
    TaskmanagerNode();
    void addTask(Task task);
    void cancelTask();
private:
    std::vector<Task> allTask;
    ros::NodeHandle nh_;
    void InitParameter();
};

#endif // TASKMANAGER_NODE_H
