#ifndef TASK_H
#define TASK_H

#include "takeoffclient.h"
#include "landingclient.h"
#include <vector>

enum PRIORITY {low, medium, high, emergency};

class Task{
public:
    Task();
    Task(std::string taskName, int id, PRIORITY priority);
    void addAction(actionClient *client);
    bool executeTask();
    void cancelTask();
private:
    std::vector<actionClient*> allClients;
    std::string taskName;
    int id;
    PRIORITY priority;
};

#endif // TASK_H
