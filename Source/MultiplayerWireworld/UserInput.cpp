#include "MultiplayerWireworld/UserInput.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/MultiplayerAutomaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"

using namespace MultiplayerWireworld;

UserInput::UserInput(std::shared_ptr<MultiplayerAutomaton> automaton)
{
  this->automaton = automaton;
  placing_shape = false;
}

void UserInput::set_canvas_position(int x, int y) { canvas_position = {x, y}; }

bool UserInput::are_coords_valid(ScreenCoords coords) const
{
  if (coords.x < canvas_position.x || coords.y < canvas_position.y)
    return false;

  return true;
}

void UserInput::update(sf::RenderTarget& canvas, sf::Event event)
{
  // Get rid of the 'unused variable' error
  (void)(canvas);

  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Num1)
      current_shape_type = Shape::SINGLE_CELL;
    else if (event.key.code == sf::Keyboard::Num2)
      current_shape_type = Shape::RECTANGLE;
    else if (event.key.code == sf::Keyboard::Num3)
      current_shape_type = Shape::LINE;
    else if (event.key.code == sf::Keyboard::Escape)
      placing_shape = false;
    else if (event.key.code == sf::Keyboard::BackSpace)
      closed = true;
    else if (event.key.code == sf::Keyboard::Space)
      automaton->advance();
  }
  else if (event.type == sf::Event::MouseButtonPressed)
    begin_shape({event.mouseButton.x, event.mouseButton.y});
  else if (event.type == sf::Event::MouseButtonReleased)
    end_shape({event.mouseButton.x, event.mouseButton.y});
  else if (event.type == sf::Event::MouseMoved)
    update_shape({event.mouseMove.x, event.mouseMove.y});
}

void UserInput::begin_shape(ScreenCoords coords)
{
  if (!are_coords_valid(coords)) return;
  last_position = current_position = screen_to_cell(coords);
  placing_shape = true;
}

void UserInput::end_shape(ScreenCoords coords)
{
  if (!placing_shape) return;
  if (!are_coords_valid(coords)) return;
  current_position = screen_to_cell(coords);
  place_shape();
  placing_shape = false;
}

void UserInput::update_shape(ScreenCoords coords)
{
  if (!placing_shape) return;
  if (!are_coords_valid(coords)) return;

  current_position = screen_to_cell(coords);
}

Position UserInput::screen_to_cell(ScreenCoords coords) const
{
  coords.x -= canvas_position.x;
  coords.y -= canvas_position.y;
  return {coords.x / 10, coords.y / 10};
}

void UserInput::place_shape() const { automaton->set_shape(current_shape()); }

bool UserInput::was_closed() { return closed; }

#include <iostream>
void UserInput::preview_current_shape(sf::RenderTarget& canvas) const
{
  if (!placing_shape) return;
  for (auto cell : current_shape()->get_cells())
  {
    sf::Color cell_color = {200, 200, 200, 200};
    sf::RectangleShape rect;
    rect.setSize({10.0f, 10.0f});
    rect.setFillColor(cell_color);
    rect.setPosition(cell.position.x * 10, cell.position.y * 10);
    canvas.draw(rect);
  }
}

std::unique_ptr<Rectangle> make_rectangle(
    Position A, Position B, Cell::Type cell_type)
{
  int x1 = std::min(A.x, B.x);
  int x2 = std::max(A.x, B.x);

  int y1 = std::min(A.y, B.y);
  int y2 = std::max(A.y, B.y);

  Position top_left = {x1, y1};
  Position bottom_right = {x2, y2};

  return std::make_unique<Rectangle>(cell_type, top_left, bottom_right);
}

std::unique_ptr<Line> make_line(Position A, Position B, Cell::Type cell_type)
{
  if (B.x < A.x) std::swap(A, B);
  return std::make_unique<Line>(cell_type, A, B);
}

std::unique_ptr<Shape> UserInput::current_shape() const
{
  std::unique_ptr<Shape> shape;
  Cell::Type current_cell_type = Cell::HEAD;
  switch (current_shape_type)
  {
    case Shape::SINGLE_CELL:
      shape = std::make_unique<SingleCell>(current_cell_type, current_position);
      break;
    case Shape::RECTANGLE:
      shape =
          make_rectangle(last_position, current_position, current_cell_type);
      break;
    case Shape::LINE:
      shape = make_line(last_position, current_position, current_cell_type);
      break;
  }
  return shape;
}

