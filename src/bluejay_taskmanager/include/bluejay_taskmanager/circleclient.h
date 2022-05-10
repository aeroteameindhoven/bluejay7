#ifndef CIRCLECLIENT_H
#define CIRCLECLIENT_H

#include "bluejay_msgs/CircleAction.h"
#include "actionclient.h"

class circleClient : public actionClient{
public:
    circleClient();
    circleClient(int _delayTime);
    circleClient(int _delayTime, bluejay_msgs::CircleGoal _goal);
    virtual bool execute();
    virtual std::string toString();

    void addGoal(bluejay_msgs::CircleGoal _goal);

private:
    bluejay_msgs::CircleGoal goal;
    bluejay_msgs::CircleFeedback feedback;
    bluejay_msgs::CircleResult result;
};


#endif // CIRCLECLIENT_H
