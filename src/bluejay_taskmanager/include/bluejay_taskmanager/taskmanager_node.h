#ifndef TASKMANAGER_NODE_H
#define TASKMANAGER_NODE_H

#include <ros/ros.h>
#include <vector>
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
    thread_pool pool{4};
};

#endif // TASKMANAGER_NODE_H
