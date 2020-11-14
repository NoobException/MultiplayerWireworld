#include <vector>

#include "../test_macro.hpp"
#include "MultiplayerWireworld/Automaton.hpp"

namespace multiplayer_wireworld_automaton
{
using namespace MultiplayerWireworld;

namespace automaton
{
void returned_cell_count_is_equal_to_requested_position_count()
{
  Automaton a;
  std::list<Position> positions_to_get = {{0, 0}, {0, 1}, {-1, 1}};
  auto cells = a.getCells(positions_to_get);
  ASSERT_EQ(positions_to_get.size(), cells.size());
}

void unset_cells_are_empty()
{
  Automaton a;
  std::list<Position> positions_to_get = {{0, 0}, {0, 1}};
  auto cells = a.getCells(positions_to_get);
  std::list<Cell> expected_cells = {
      {Cell::EMPTY, {0, 0}}, {Cell::EMPTY, {0, 1}}};
  ASSERT_EQ(cells, expected_cells);
}

void cells_persist_set_state()
{
  Automaton a;
  std::list<Cell> cells_to_set;
  cells_to_set.push_back({Cell::CONDUCTOR, {0, 0}});
  cells_to_set.push_back({Cell::HEAD, {0, 1}});
  cells_to_set.push_back({Cell::TAIL, {1, 0}});
  a.setCells(cells_to_set);

  std::list<Position> positions_to_get = {{0, 0}, {0, 1}, {1, 0}};
  auto cells = a.getCells(positions_to_get);
  ASSERT_EQ(cells_to_set, cells);
}

void run_all_tests()
{
  begin_group("multiplayer_wireworld_automaton::automaton");
  test(returned_cell_count_is_equal_to_requested_position_count);
  test(unset_cells_are_empty);
  test(cells_persist_set_state);
  end_group("multiplayer_wireworld_automaton::automaton");
}
}  // namespace automaton
}  // namespace multiplayer_wireworld_automaton

