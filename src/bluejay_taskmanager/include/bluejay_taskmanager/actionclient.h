#ifndef ACTIONCLIENT_H
#define ACTIONCLIENT_H

#include <string>
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

class actionClient
{
public:
    virtual ~actionClient(){}
    virtual bool execute() = 0;
    virtual std::string toString() = 0;
protected:
    std::string clientName;
    int id;
    int delayTime;
};
#endif // ACTIONCLIENT_H
