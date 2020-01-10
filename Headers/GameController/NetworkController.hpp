#ifndef GAMECONTROLLER_NETWORKCONTROLLER_HPP
#define GAMECONTROLLER_NETWORKCONTROLLER_HPP

namespace GameController
{
class NetworkController
{
public:
    virtual void controllerLoop() = 0;
    virtual bool hasNextEvent() = 0;
    virtual NetworkEvent *getNextEvent() = 0;
    virtual void sendEvent(NetworkEvent *event) = 0;
    virtual void stop() = 0;
};
} // GameController

#endif // GAMECONTROLLER_NETWORKCONTROLLER_HPP
