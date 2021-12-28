#ifndef TAKEOFFCLIENT_H
#define TAKEOFFCLIENT_H

#include "actionclient.h"


class takeoffClient : public actionClient{
public:
    takeoffClient();
    bool executed();
    std::string toString();

private:

};

#endif // TAKEOFFCLIENT_H
