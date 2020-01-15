#ifndef GAMECONTROLLER_COMPONENTCONTROLLER_HPP
#define GAMECONTROLLER_COMPONENTCONTROLLER_HPP

#include <memory>

#include "GameController/GameEvent.hpp"

namespace GameController
{
class ComponentController
{
public:
    virtual std::unique_ptr<GameEvent> get_next_game_event() = 0;
    virtual bool has_next_game_event() = 0;
};
} // namespace GameController

#endif //GAMECONTROLLER_COMPONENTCONTROLLER_HPP