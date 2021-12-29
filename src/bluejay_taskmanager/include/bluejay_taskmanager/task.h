#ifndef TASK_H
#define TASK_H

#include "takeoffclient.h"
#include "landingclient.h"

#include <vector>

class Task{
public:
    Task();
    bool addAction(actionClient *client);
    bool executeTask();
private:
    std::vector<actionClient*> allClients;
    int id;
};

#endif // TASK_H
