#ifndef moveClient_H
#define moveClient_H
#include "actionclient.h"
#include "bluejay_msgs/MoveAction.h"

class moveClient : public actionClient{
public:
    moveClient();
    moveClient(int _delayTime);
    moveClient(int _delayTime, bluejay_msgs::MoveGoal _goal);
    virtual bool execute();
    virtual std::string toString();

    void addGoal(bluejay_msgs::MoveGoal _goal);

private:
    bluejay_msgs::MoveGoal goal;
    bluejay_msgs::MoveFeedback feedback;
    bluejay_msgs::MoveResult result;
};


#endif // moveClient_H
