#include "MultiplayerWireworld/WireworldNetwork.hpp"

#include "Grid/Shapes.hpp"
#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"

using namespace MultiplayerWireworld;
using namespace Grid;

#define UNUSED(x) (void)(x)

#include <iostream>

void cerr_pos(Position p) { std::cerr << "(" << p.x << ", " << p.y << ")"; }

class ShapeToPacket : public ConstShapeVisitor
{
public:
  void visit_shape(const Shape& shape)
  {
    std::cerr << "Visiting " + shape_type_to_string(shape.type()) << ": ";
  }

  void visit(const SingleCell& s) override
  {
    visit_shape(s);
    cerr_pos(s.position);
    std::cerr << "\n";
    UNUSED(s);
  }

  void visit(const Rectangle& r) override
  {
    visit_shape(r);
    cerr_pos(r.top_left_corner);
    std::cerr << " ";
    cerr_pos(r.bottom_right_corner);
    std::cerr << "\n";
    UNUSED(r);
  }

  void visit(const Line& l) override
  {
    visit_shape(l);
    cerr_pos(l.left_end);
    std::cerr << " ";
    cerr_pos(l.right_end);
    std::cerr << "\n";
    UNUSED(l);
  }
};

class ActionToPacket : public ActionVisitor
{
public:
  void visit(SetShape& action) override
  {
    auto cell_type_string = cell_type_to_string(action.cell_shape.cell.type);
    std::cerr << "Visiting SetShape [" << cell_type_string << "]\n";
    ShapeToPacket shape_to_packet;
    action.cell_shape.shape->accept(shape_to_packet);
    UNUSED(action);
  }

  void visit(Advance& action) override
  {
    std::cerr << "Visiting Advance\n";
    UNUSED(action);
  }
};

void WireworldNetwork::send_action(std::unique_ptr<Action> action)
{
  ActionToPacket action_to_packet;
  action->accept(action_to_packet);
}

