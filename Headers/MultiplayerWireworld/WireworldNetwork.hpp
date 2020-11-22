#ifndef WIREWORLD_NETWORK_HPP
#define WIREWORLD_NETWORK_HPP

#include <SFML/Network.hpp>
#include <list>
#include <memory>

#include "MultiplayerWireworld/Shapes.hpp"

namespace MultiplayerWireworld
{
struct SetShape;
struct Advance;

class ActionVisitor
{
public:
  virtual void visit(SetShape&) = 0;
  virtual void visit(Advance&) = 0;
};

struct Action
{
  virtual void accept(ActionVisitor&) = 0;
  virtual ~Action() = default;
};

struct SetShape : public Action
{
  const CellShape& cell_shape;
  SetShape(const CellShape& shape) : cell_shape(shape) {}
  void accept(ActionVisitor& visitor) override { visitor.visit(*this); };
};

struct Advance : public Action
{
  void accept(ActionVisitor& visitor) override { visitor.visit(*this); };
};

class WireworldNetwork
{
public:
  void send_action(std::unique_ptr<Action> action);
  std::list<std::unique_ptr<Action>> receiveActions();
};

}  // namespace MultiplayerWireworld
#endif
