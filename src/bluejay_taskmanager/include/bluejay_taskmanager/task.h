#ifndef TASK_H
#define TASK_H

#include "takeoffclient.h"
#include <vector>

class Task{
public:
    Task();
    void addAction(actionClient *client);
    bool executeTask();
private:
    std::vector<actionClient*> allClients;
    int id;
};

#endif // TASK_H
