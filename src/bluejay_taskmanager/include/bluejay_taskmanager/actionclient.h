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
    virtual bool executed() = 0;
    virtual std::string toString() = 0;
private:
    std::string clientName;
    int id;
};
#endif // ACTIONCLIENT_H
