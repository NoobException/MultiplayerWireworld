#ifndef GAMECONTROLLER_NETWORKCONTROLLER_HPP
#define GAMECONTROLLER_NETWORKCONTROLLER_HPP

#include "GameController/GameEvent.hpp"

namespace GameController
{
class NetworkController
{
public:
    virtual void send_event(const GameEvent &) = 0;
};
} // namespace GameController

#endif // GAMECONTROLLER_NETWORKCONTROLLER_HPP
