#include <set>

#include "../test_macro.hpp"
#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"

namespace multiplayer_wireworld_shapes
{
using namespace MultiplayerWireworld;
namespace shapes
{
template <typename T>
bool list_contains(std::list<T> elements, T value)
{
  for (auto el : elements)
    if (el == value) return true;

  return false;
}
bool list_cells_are_unique(std::list<Cell> cells)
{
  std::set<Position> positions;
  for (auto cell : cells) positions.insert(cell.position);
  return cells.size() == positions.size();
}

namespace line
{
bool contains_both_ends(Position left_end, Position right_end)
{
  std::list<Cell> cells = Line(Cell::EMPTY, left_end, right_end).getCells();
  std::list<Position> positions;
  for (auto cell : cells) positions.push_back(cell.position);

  return list_contains(positions, left_end) &&
         list_contains(positions, right_end);
}

bool unique_cells(Position left_end, Position right_end)
{
  std::list<Cell> cells = Line(Cell::EMPTY, left_end, right_end).getCells();
  return list_cells_are_unique(cells);
}
void vertical_cells_are_unique()
{
  Position left_end = {0, 4};
  Position right_end = {0, 0};
  ASSERT(unique_cells(left_end, right_end));
}

void horizontal_cells_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {4, 0};
  ASSERT(unique_cells(left_end, right_end));
}

void with_45_degree_slope_cells_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {3, 3};
  ASSERT(unique_cells(left_end, right_end));
}

void with_slope_greater_than_45_degrees_cells_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {3, 8};
  ASSERT(unique_cells(left_end, right_end));
}

void with_slope_less_than_45_degrees_cells_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {8, 3};
  ASSERT(unique_cells(left_end, right_end));
}

void with_negative_slope_cells_are_unique()
{
  Position left_end = {0, -3};
  Position right_end = {0, -8};
  ASSERT(unique_cells(left_end, right_end));
}

void vertical_cells_contain_both_ends()
{
  Position left_end = {0, 4};
  Position right_end = {0, 0};
  ASSERT(contains_both_ends(left_end, right_end));
}

void horizontal_cells_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {4, 0};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_45_degree_slope_cells_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {3, 3};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_slope_greater_than_45_degrees_cells_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {3, 8};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_slope_less_than_45_degrees_cells_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {8, 3};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_negative_slope_cells_contain_both_ends()
{
  Position left_end = {0, -3};
  Position right_end = {0, -8};
  ASSERT(contains_both_ends(left_end, right_end));
}

void run_all_tests()
{
  begin_group("line");
  test(vertical_cells_are_unique);
  test(horizontal_cells_are_unique);
  test(with_45_degree_slope_cells_are_unique);
  test(with_slope_greater_than_45_degrees_cells_are_unique);
  test(with_slope_less_than_45_degrees_cells_are_unique);
  test(with_negative_slope_cells_are_unique);

  test(vertical_cells_contain_both_ends);
  test(horizontal_cells_contain_both_ends);
  test(with_45_degree_slope_cells_contain_both_ends);
  test(with_slope_greater_than_45_degrees_cells_contain_both_ends);
  test(with_slope_less_than_45_degrees_cells_contain_both_ends);
  test(with_negative_slope_cells_contain_both_ends);
  end_group("line");
}
}  // namespace line

namespace rectangle
{
void cells_are_unique()
{
  Position top_left_corner = {10, 0};
  Position bottom_right_corner = {0, 10};

  std::list<Cell> cells =
      Rectangle(Cell::EMPTY, top_left_corner, bottom_right_corner).getCells();
  ASSERT(list_cells_are_unique(cells));
}

void run_all_tests()
{
  begin_group("rectangle");
  test(cells_are_unique);
  end_group("rectangle");
}
};  // namespace rectangle

}  // namespace shapes
void run_all_tests()
{
  begin_group("multiplayer_wireworld_shapes");
  shapes::rectangle::run_all_tests();
  shapes::line::run_all_tests();
  end_group("multiplayer_wireworld_shapes");
}
}  // namespace multiplayer_wireworld_shapes

