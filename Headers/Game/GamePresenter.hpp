#ifndef GAME_GAMEPRESENTER_HPP
#define GAME_GAMEPRESENTER_HPP

#include "Game/Grid.hpp"

namespace Game
{
class GamePresenter
{
public:
    virtual void draw_grid(const Grid &) = 0;
};
} // namespace Game

#endif //  GAMECONTROLLER_HPP