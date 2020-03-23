#ifndef NETWORKEVENT_HPP
#define NETWORKEVENT_HPP

#include <SFML/Network.hpp>

#include "Game/Game.hpp"

namespace Network
{
class NetworkEvent
{
public:
    enum Type
    {
        NEW_CLIENT,
        CELL_CHANGED,
        RECTANGLE_CHANGED,
        LINE_CHANGED,
        ADVANCE_SIMULATION,
        CLEAR_WIRES
    };
    virtual Type getType() = 0;
    virtual sf::Packet toPacket() = 0;
    virtual void apply(Game::Game &) = 0;
};
} // namespace Network
#endif