#include <SFML/Graphics.hpp>

#include "Wireworld/GridRenderer.hpp"
#include "Wireworld/Cell.hpp"
#include "Wireworld/Cells.hpp"

using namespace Wireworld;

void GridRenderer::draw_cells(
    sf::RenderTarget& target, 
    const Game::Cells& game_cells)
{
    const Cells& cells = static_cast<const Cells&>(game_cells);
    for (Cell cell : cells)
    {
        draw_cell(target, cell);
    }
}
void GridRenderer::draw_cell(
    sf::RenderTarget& target,
    Cell& cell)
{
    sf::Color color;

    switch (cell.state.type)
    {
    case Cell::State::Empty:
        color = {20, 20, 20};
        break;
    case Cell::State::Head:
        color = {200, 80, 30};
        break;
    case Cell::State::Tail:
        color = {30, 120, 220};
        break;
    case Cell::State::Conductor:
        color = {200, 200, 80};
        break;
    default:
        color = {255, 255, 255};
    }

    sf::RectangleShape rect;
    rect.setSize({10.0f, 10.0f});
    rect.setFillColor(color);
    rect.setPosition(cell.coords.x * 10, cell.coords.y * 10);
    target.draw(rect);
}
