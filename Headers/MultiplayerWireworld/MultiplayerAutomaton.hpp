#ifndef MULTIPLAYER_AUTOMATON
#define MULTIPLAYER_AUTOMATON

#include <memory>

#include "Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"
#include "WireworldNetwork.hpp"

namespace MultiplayerWireworld
{
struct MultiplayerCell
{
  Cell cell;
  bool is_ghost;
  bool operator==(const MultiplayerCell &) const;
};

class MultiplayerAutomaton
{
public:
  void set_shape(const CellShape &);
  void set_cells(const std::list<Cell> &);
  void advance();
  std::list<MultiplayerCell> get_cells(const std::list<Position> &) const;

private:
  std::unique_ptr<WireworldNetwork> wireworld_network;
  Automaton automaton;
};
}  // namespace MultiplayerWireworld
#endif
