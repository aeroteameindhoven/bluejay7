#ifndef ACTIONCLIENT_H
#define ACTIONCLIENT_H

#include <string>
#include <ros/ros.h>

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
