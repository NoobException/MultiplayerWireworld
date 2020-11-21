#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <list>

#include "Grid.hpp"

namespace Grid
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

  virtual ~Shape() = default;
  virtual Shape::Type type() const = 0;
  virtual void accept(ShapeVisitor&) = 0;
  virtual void accept(ConstShapeVisitor&) const = 0;
  virtual std::list<Position> positions() const = 0;
};

struct SingleCell : public Shape
{
  Position position;

  SingleCell(Position position);

  Shape::Type type() const override { return SINGLE_CELL; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
  std::list<Position> positions() const override;
};

struct Rectangle : public Shape
{
  Position top_left_corner, bottom_right_corner;

  Rectangle(Position top_left_corner, Position bottom_right_corner);
  Shape::Type type() const override { return RECTANGLE; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
  std::list<Position> positions() const override;
};

struct Line : public Shape
{
  Position left_end, right_end;

  Line(Position left_end, Position right_end);

  Shape::Type type() const override { return LINE; }
  void accept(ShapeVisitor& visitor) override { visitor.visit(*this); }
  void accept(ConstShapeVisitor& visitor) const override
  {
    visitor.visit(*this);
  }
  std::list<Position> positions() const override;
};

}  // namespace Grid
#endif
