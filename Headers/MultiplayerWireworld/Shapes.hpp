#ifndef MULTIPLAYER_WIREWORLD_SHAPES_HPP
#define MULTIPLAYER_WIREWORLD_SHAPES_HPP

#include <list>
#include <memory>

#include "MultiplayerWireworld/Automaton.hpp"

namespace MultiplayerWireworld
{
struct Cells
{
  virtual std::list<Cell> get_cells() const = 0;
  virtual ~Cells() = default;
};

struct SingleCell : public Cells
{
  Cell::Type cell_type;
  Position position;

  SingleCell(Cell::Type, Position position);
  std::list<Cell> get_cells() const override;
};

struct Rectangle : public Cells
{
  Cell::Type cell_type;
  Position top_left_corner, bottom_right_corner;
  Rectangle(Cell::Type, Position top_left_corner, Position bottom_right_corner);
  std::list<Cell> get_cells() const override;
};

struct Line : public Cells
{
  Cell::Type cell_type;
  Position left_end, right_end;
  Line(Cell::Type, Position left_end, Position right_end);
  std::list<Cell> get_cells() const override;
};

struct Shape
{
  enum Type
  {
    SINGLE_CELL,
    RECTANGLE,
    LINE
  } type;

  union
  {
    SingleCell single_cell;
    Rectangle rectangle;
    Line line;
  };

  std::unique_ptr<Cells> shape;

  Shape(){};

  Shape(Rectangle r)
  {
    shape = std::make_unique<Rectangle>(r);
    type = RECTANGLE;
    rectangle = r;
  }

  Shape(Line l)
  {
    shape = std::make_unique<Line>(l);
    type = LINE;
    line = l;
  }

  Shape(SingleCell s)
  {
    shape = std::make_unique<SingleCell>(s);
    type = SINGLE_CELL;
    single_cell = s;
  }

  std::list<Cell> get_cells() const { return shape->get_cells(); }
  Type get_type() const { return type; }

  ~Shape()
  {
    if (type == SINGLE_CELL) single_cell.~SingleCell();
    if (type == RECTANGLE) rectangle.~Rectangle();
    if (type == LINE) line.~Line();
  }
};
}  // namespace MultiplayerWireworld
#endif
