#include "MultiplayerWireworld/Renderer.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "MultiplayerWireworld/MultiplayerAutomaton.hpp"

using namespace MultiplayerWireworld;

Renderer::Renderer(std::shared_ptr<MultiplayerAutomaton> automaton)
{
  this->automaton = automaton;
}

void Renderer::render_cell(sf::RenderTarget& canvas, MultiplayerCell cell) const
{
  sf::Color cell_color;
  switch (cell.cell.type)
  {
    case Cell::EMPTY:
      cell_color = {20, 20, 20};
      break;
    case Cell::HEAD:
      cell_color = {200, 80, 30};
      break;
    case Cell::TAIL:
      cell_color = {30, 120, 220};
      break;
    case Cell::CONDUCTOR:
      cell_color = {200, 200, 80};
      break;
  }

  if (cell.is_ghost) cell_color.a = 128;

  sf::RectangleShape rect;
  rect.setSize({10.0f, 10.0f});
  rect.setFillColor(cell_color);
  rect.setPosition(cell.cell.position.x * 10, cell.cell.position.y * 10);
  canvas.draw(rect);
}
void Renderer::render(sf::RenderTarget& canvas) const
{
  std::list<Position> positions_to_render;
  for (int x = 0; x < 64; x++)
    for (int y = 0; y < 64; y++) positions_to_render.push_back({x, y});

  std::list<MultiplayerCell> cells_to_render =
      automaton->get_cells(positions_to_render);

  for (auto cell : cells_to_render) render_cell(canvas, cell);
}
