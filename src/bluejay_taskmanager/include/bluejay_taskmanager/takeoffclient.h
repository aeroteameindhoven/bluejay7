#ifndef TAKEOFFCLIENT_H
#define TAKEOFFCLIENT_H

#include "actionclient.h"
#include "bluejay_msgs/TakeOffAction.h"

class takeoffClient : public actionClient{
public:
    takeoffClient();
    takeoffClient(int _delayTime);
    takeoffClient(int _delayTime, bluejay_msgs::TakeOffGoal _goal);
    virtual bool execute();
    virtual std::string toString();

    void addGoal(bluejay_msgs::TakeOffGoal _goal);

private:
    bluejay_msgs::TakeOffGoal goal;
    bluejay_msgs::TakeOffFeedback feedback;
    bluejay_msgs::TakeOffResult result;
};

#endif // TAKEOFFCLIENT_H
