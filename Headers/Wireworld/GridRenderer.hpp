#ifndef WIREWORLD_GRIDRENDERER_HPP
#define WIREWORLD_GRIDRENDERER_HPP

#include "Game/Cell.hpp"
#include "UI/GridRenderer.hpp"

namespace Wireworld
{
class GridRenderer : public UI::GridRenderer
{
public:
    void draw_cell(std::unique_ptr<Game::Cell>) override;
};

} // namespace Wireworld

#endif // WIREWORLD_GRIDRENDERER_HPP
