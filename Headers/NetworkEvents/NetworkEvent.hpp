#ifndef NETWORKEVENT_HPP
#define NETWORKEVENT_HPP

#include <SFML/Network.hpp>
#include "Game.hpp"
enum Type
{
    NEW_CLIENT,
    CELL_CHANGED,
    ADVANCE_SIMULATION
};
class NetworkEvent
{
public:
    virtual Type getType() = 0;
    virtual sf::Packet toPacket() = 0;
    virtual void apply(Game &game) = 0;
};
#endif