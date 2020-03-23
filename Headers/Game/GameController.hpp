#ifndef GAME_GAMECONTROLLER_HPP
#define GAME_GAMECONTROLLER_HPP

#include <memory>

#include "Game/GameEvent.hpp"

namespace Game
{
class GameController
{
public:
    virtual std::unique_ptr<GameEvent> get_next_game_event();
    virtual bool has_next_game_event();
};
} // namespace Game

#endif // GAME_GAMECONTROLLER_HPP