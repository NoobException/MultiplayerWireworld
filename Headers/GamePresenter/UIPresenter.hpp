#ifndef GAMEPRESENTER_UIPRESENTER_HPP
#define GAMEPRESENTER_UIPRESENTER_HPP

#include "Game/Grid.hpp"

namespace GamePresenter
{
class UIPresenter
{
public:
    virtual void draw_grid(const Game::Grid &) = 0;
};
} // namespace GamePresenter

#endif // GAMEPRESENTER_UIPRESENTER_HPP