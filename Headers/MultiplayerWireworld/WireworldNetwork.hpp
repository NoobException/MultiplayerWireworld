#ifndef WIREWORLD_NETWORK_HPP
#define WIREWORLD_NETWORK_HPP

#include <list>

namespace MultiplayerWireworld
{
struct Action
{
  enum Type
  {
    Shape,
    Advance
  };
};

class WireworldNetwork
{
public:
  void sendAction(Action);
  std::list<Action> receiveActions();
};
}  // namespace MultiplayerWireworld
#endif
