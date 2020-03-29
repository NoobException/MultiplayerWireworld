#ifndef WIREWORLD_GRIDRENDERER_HPP
#define WIREWORLD_GRIDRENDERER_HPP

#include <SFML/Graphics.hpp>

#include "Game/Cells.hpp"
#include "UI/GridRenderer.hpp"
#include "Wireworld/Cell.hpp"

namespace Wireworld
{
class GridRenderer : public UI::GridRenderer
{
public:
    void draw_cells(sf::RenderTarget&, const Game::Cells&) override;
private:
    void draw_cell(sf::RenderTarget&, Cell&);
};

} // namespace Wireworld

#endif // WIREWORLD_GRIDRENDERER_HPP
