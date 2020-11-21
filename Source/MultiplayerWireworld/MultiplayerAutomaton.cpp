#include "MultiplayerWireworld/MultiplayerAutomaton.hpp"

#include "MultiplayerWireworld/WireworldNetwork.hpp"

using namespace MultiplayerWireworld;

bool MultiplayerCell::operator==(const MultiplayerCell& rhs) const
{
  return cell == rhs.cell && is_ghost == rhs.is_ghost;
}

void MultiplayerAutomaton::set_cells(const std::list<Cell>& cells)
{
  automaton.set_cells(cells);
}

std::list<MultiplayerCell> MultiplayerAutomaton::get_cells(
    const std::list<Position>& positions) const
{
  std::list<Cell> non_ghost_cells = automaton.get_cells(positions);
  std::list<MultiplayerCell> cells;
  for (auto cell : non_ghost_cells) cells.push_back({cell, false});
  return cells;
}

void MultiplayerAutomaton::set_shape(const CellShape& shape)
{
  set_cells(shape.cells());
  wireworld_network->send_action(std::make_unique<SetShape>(shape));
}

void MultiplayerAutomaton::advance()
{
  automaton.advance();
  wireworld_network->send_action(std::make_unique<Advance>());
}

