#include "MultiplayerWireworld/WireworldNetwork.hpp"

#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"

using namespace MultiplayerWireworld;

#define UNUSED(x) (void)(x)

#include <iostream>

void cerr_pos(Position p) { std::cerr << "(" << p.x << ", " << p.y << ")"; }

class ShapeToPacket : public ConstShapeVisitor
{
public:
  void visit(const SingleCell& s)
  {
    std::cerr << "Visiting SingleCell: ";
    cerr_pos(s.position);
    std::cerr << "\n";
    UNUSED(s);
  }

  void visit(const Rectangle& r)
  {
    std::cerr << "Visiting Rectangle: ";
    cerr_pos(r.top_left_corner);
    std::cerr << " ";
    cerr_pos(r.bottom_right_corner);
    std::cerr << "\n";
    UNUSED(r);
  }

  void visit(const Line& l)
  {
    std::cerr << "Visiting Line: ";
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
    std::cerr << "Visiting SetShape\n";
    ShapeToPacket shape_to_packet;
    action.shape.get().accept(shape_to_packet);
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

