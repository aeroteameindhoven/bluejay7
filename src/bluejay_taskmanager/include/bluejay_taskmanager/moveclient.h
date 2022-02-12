#ifndef MOVECLIENT_H
#define MOVECLIENT_H
#include "actionclient.h"
#include "bluejay_msgs/MoveAction.h"

class MoveClient : public actionClient{
public:
    MoveClient();
    MoveClient(int _delayTime);
    MoveClient(int _delayTime, bluejay_msgs::MoveGoal _goal);
    virtual bool execute();
    virtual std::string toString();

    void addGoal(bluejay_msgs::MoveGoal _goal);

private:
    bluejay_msgs::MoveGoal goal;
    bluejay_msgs::MoveFeedback feedback;
    bluejay_msgs::MoveResult result;
};


#endif // MOVECLIENT_H
