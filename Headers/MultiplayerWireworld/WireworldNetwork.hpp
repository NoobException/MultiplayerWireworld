#ifndef WIREWORLD_NETWORK_HPP
#define WIREWORLD_NETWORK_HPP

#include <SFML/Network.hpp>
#include <functional>
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
  std::reference_wrapper<const Shape> shape;
  SetShape(const Shape& shape) : shape(std::cref(shape)) {}

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
