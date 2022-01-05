#ifndef FAKECLIENT_H
#define FAKECLIENT_H

#include "bluejay_msgs/LandingAction.h"
#include "actionclient.h"

class fakeClient : public actionClient{
public:
    fakeClient();

    fakeClient(std::string _message);

    virtual bool execute();
    virtual std::string toString();

    void addGoal();

private:
    std::string message;
};

#endif // FAKECLIENT_H
