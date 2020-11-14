#ifndef MULTIPLAYER_WIREWORLD_SHAPES_HPP
#define MULTIPLAYER_WIREWORLD_SHAPES_HPP

#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/MultiplayerAutomaton.hpp"

namespace MultiplayerWireworld
{
class SingleCell : public Shape
{
  Cell::Type cell_type;
  Position position;

public:
  SingleCell(Cell::Type, Position);
  std::list<Cell> get_cells() const override;
  Type type() const override;
};

class Rectangle : public Shape
{
  Cell::Type cell_type;
  Position top_left_corner, bottom_right_corner;

public:
  Rectangle(Cell::Type, Position, Position);
  std::list<Cell> get_cells() const override;
  Type type() const override;
};

class Line : public Shape
{
  Cell::Type cell_type;
  Position left_end, right_end;

public:
  Line(Cell::Type, Position, Position);
  std::list<Cell> get_cells() const override;
  Type type() const override;
};

}  // namespace MultiplayerWireworld
#endif
