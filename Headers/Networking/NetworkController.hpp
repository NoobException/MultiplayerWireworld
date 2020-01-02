#ifndef NETWORKCONTROLLER_HPP
#define NETWORKCONTROLLER_HPP

#include "NetworkEvents/Events.hpp"

class NetworkController
{
    virtual void controllerLoop() = 0;
    virtual bool hasNextEvent() = 0;
    virtual NetworkEvent *getNextEvent() = 0;
    virtual void sendEvent(NetworkEvent *event) = 0;
    virtual void stop() = 0;
};

#endif // NETWORKCONTROLLER_HPP
