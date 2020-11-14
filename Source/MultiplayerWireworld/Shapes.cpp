#include "MultiplayerWireworld/Shapes.hpp"

#include <memory>

#include "MultiplayerWireworld/Automaton.hpp"
using namespace MultiplayerWireworld;

SingleCell::SingleCell(Cell::Type cell_type, Position position)
{
  this->cell_type = cell_type;
  this->position = position;
}
std::list<Cell> SingleCell::get_cells() const
{
  return {{cell_type, position}};
}

Shape::Type SingleCell::type() const { return Shape::SINGLE_CELL; }

Rectangle::Rectangle(
    Cell::Type cell_type, Position top_left_corner,
    Position bottom_right_corner)
{
  this->cell_type = cell_type;
  this->top_left_corner = top_left_corner;
  this->bottom_right_corner = bottom_right_corner;
}
std::list<Cell> Rectangle::get_cells() const
{
  std::list<Cell> result;
  for (int x = top_left_corner.x; x <= bottom_right_corner.x; x++)
    for (int y = top_left_corner.y; y <= bottom_right_corner.y; y++)
    { result.push_back({cell_type, {x, y}}); }
  return result;
}

Shape::Type Rectangle::type() const { return Shape::RECTANGLE; }

Line::Line(Cell::Type cell_type, Position left_end, Position right_end)
{
  this->cell_type = cell_type;
  this->left_end = left_end;
  this->right_end = right_end;
}

int sign(int value)
{
  if (value < 0)
    return -1;
  else if (value == 0)
    return 0;
  else
    return 1;
}
#include <iostream>
std::list<Cell> Line::get_cells() const
{
  std::list<Cell> result;

  int dx = (right_end.x - left_end.x);
  int dy = (right_end.y - left_end.y);
  int dxm = (dx * left_end.y - dy * left_end.x);

  int first_dx = 0, first_dy = 0;
  int second_dx = 0, second_dy = 0;

  if (std::abs(left_end.y - right_end.y) <= std::abs(left_end.x - right_end.x))
  {
    first_dx = second_dx = 1;
    second_dy = sign(dy);
  }
  else
  {
    first_dy = second_dy = sign(dy);
    second_dx = sign(dx);
  }

  Position current_position = left_end;
  result.push_back({cell_type, current_position});
  while (!(current_position == right_end))
  {
    Position p1 = current_position, p2 = current_position;
    p1.x += first_dx;
    p1.y += first_dy;

    p2.x += second_dx;
    p2.y += second_dy;

    if (std::abs(dy * p1.x - dx * p1.y + dxm) <
        std::abs(dy * p2.x - dx * p2.y + dxm))
    { current_position = p1; }
    else
    {
      current_position = p2;
    }

    result.push_back({cell_type, current_position});
  }

  return result;
}

Shape::Type Line::type() const { return Shape::LINE; }

