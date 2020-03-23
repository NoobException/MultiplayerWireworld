#ifndef GAME_GAMEEVENT_HPP
#define GAME_GAMEEVENT_HPP

#include <memory>

#include "Game/Game.hpp"

namespace Game
{
class GameEvent
{
public:
    virtual void apply(Game &);
};
} // namespace Game
#endif // GAME_GAMEEVENT_HPP
