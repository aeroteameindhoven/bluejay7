#ifndef TAKEOFFCLIENT_H
#define TAKEOFFCLIENT_H

#include "actionclient.h"
#include "bluejay_msgs/TakeOffAction.h"


class takeoffClient : public actionClient{
public:
    takeoffClient();
    virtual bool executed();
    virtual std::string toString();

private:
    bluejay_msgs::TakeOffGoal goal;
};

#endif // TAKEOFFCLIENT_H
