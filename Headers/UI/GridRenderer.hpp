#ifndef UI_GRIDRENDERER_HPP
#define UI_GRIDRENDERER_HPP

#include <memory>

#include "Game/Cell.hpp"

namespace UI
{
class GridRenderer
{
public:
    virtual void draw_cell(std::unique_ptr<Game::Cell>) = 0;
};

} // namespace UI

#endif // UI_GRIDRENDERER_HPP
