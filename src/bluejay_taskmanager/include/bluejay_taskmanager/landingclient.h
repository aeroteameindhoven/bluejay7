#ifndef LANDINGCLIENT_H
#define LANDINGCLIENT_H

#include "bluejay_msgs/LandingAction.h"
#include "actionclient.h"

class landingClient : public actionClient{
public:
    landingClient();
    landingClient(bluejay_msgs::LandingGoal _goal);
    virtual bool executed();
    virtual std::string toString();

    void addGoal(bluejay_msgs::LandingGoal _goal);

private:
    bluejay_msgs::LandingGoal goal;
    bluejay_msgs::LandingFeedback feedback;
    bluejay_msgs::LandingResult result;
};

#endif // LANDINGCLIENT_H
