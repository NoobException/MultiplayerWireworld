#ifndef UI_GRIDRENDERER_HPP
#define UI_GRIDRENDERER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "Game/Cells.hpp"

namespace UI
{
class GridRenderer
{
public:
    virtual void draw_cells(sf::RenderTarget&, const Game::Cells&) = 0;
};

} // namespace UI

#endif // UI_GRIDRENDERER_HPP
