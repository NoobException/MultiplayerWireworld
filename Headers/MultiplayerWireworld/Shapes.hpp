#ifndef MULTIPLAYER_WIREWORLD_SHAPES_HPP
#define MULTIPLAYER_WIREWORLD_SHAPES_HPP

#include <list>
#include <memory>

#include "MultiplayerWireworld/Automaton.hpp"

namespace MultiplayerWireworld
{
// Forward declare classes that are visited
struct SingleCell;
struct Rectangle;
struct Line;

class ShapeVisitor
{
public:
  virtual void visit(SingleCell&) = 0;
  virtual void visit(Rectangle&) = 0;
  virtual void visit(Line&) = 0;
};

class ConstShapeVisitor
{
public:
  virtual void visit(const SingleCell&) = 0;
  virtual void visit(const Rectangle&) = 0;
  virtual void visit(const Line&) = 0;
};

struct Shape
{
  enum Type
  {
    SINGLE_CELL,
    RECTANGLE,
    LINE
  };

  virtual std::list<Cell> get_cells() const = 0;
  virtual ~Shape() = default;
  virtual Type type() const = 0;
  virtual void accept(ShapeVisitor&) = 0;
  virtual void accept(ConstShapeVisitor&) const = 0;
};

struct SingleCell : public Shape
{
  Cell::Type cell_type;
  Position position;

  SingleCell(Cell::Type, Position position);
  std::list<Cell> get_cells() const override;

  Shape::Type type() const override { return Shape::SINGLE_CELL; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
};

struct Rectangle : public Shape
{
  Cell::Type cell_type;
  Position top_left_corner, bottom_right_corner;

  Rectangle(Cell::Type, Position top_left_corner, Position bottom_right_corner);
  std::list<Cell> get_cells() const override;

  Shape::Type type() const override { return Shape::RECTANGLE; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
};

struct Line : public Shape
{
  Cell::Type cell_type;
  Position left_end, right_end;

  Line(Cell::Type, Position left_end, Position right_end);
  std::list<Cell> get_cells() const override;

  Shape::Type type() const override { return Shape::LINE; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
};

}  // namespace MultiplayerWireworld
#endif
