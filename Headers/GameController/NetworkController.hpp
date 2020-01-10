#ifndef GAMECONTROLLER_NETWORKCONTROLLER_HPP
#define GAMECONTROLLER_NETWORKCONTROLLER_HPP

#include "GameController/GameEvent.hpp"

namespace GameController
{
class NetworkController
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send_event(const GameEvent &);
};
} // GameController

#endif // GAMECONTROLLER_NETWORKCONTROLLER_HPP
