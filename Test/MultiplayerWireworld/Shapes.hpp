#include <set>

#include "../test_macro.hpp"
#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"

namespace grid_shapes
{
using namespace Grid;
namespace shapes
{
template <typename T>
bool list_contains(std::list<T> elements, T value)
{
  for (auto el : elements)
    if (el == value) return true;
  return false;
}
bool list_positions_are_unique(std::list<Position> shape_positions)
{
  std::set<Position> positions;
  for (auto position : shape_positions) positions.insert(position);
  return positions.size() == shape_positions.size();
}

namespace line
{
bool contains_both_ends(Position left_end, Position right_end)
{
  std::list<Position> shape_positions = Line(left_end, right_end).positions();
  std::list<Position> positions;
  for (auto position : shape_positions) positions.push_back(position);

  return list_contains(positions, left_end) &&
         list_contains(positions, right_end);
}

bool unique_positions(Position left_end, Position right_end)
{
  std::list<Position> positions = Line(left_end, right_end).positions();
  return list_positions_are_unique(positions);
}
void vertical_positions_are_unique()
{
  Position left_end = {0, 4};
  Position right_end = {0, 0};
  ASSERT(unique_positions(left_end, right_end));
}

void horizontal_positions_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {4, 0};
  ASSERT(unique_positions(left_end, right_end));
}

void with_45_degree_slope_positions_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {3, 3};
  ASSERT(unique_positions(left_end, right_end));
}

void with_slope_greater_than_45_degrees_positions_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {3, 8};
  ASSERT(unique_positions(left_end, right_end));
}

void with_slope_less_than_45_degrees_positions_are_unique()
{
  Position left_end = {0, 0};
  Position right_end = {8, 3};
  ASSERT(unique_positions(left_end, right_end));
}

void with_negative_slope_positions_are_unique()
{
  Position left_end = {0, -3};
  Position right_end = {0, -8};
  ASSERT(unique_positions(left_end, right_end));
}

void vertical_positions_contain_both_ends()
{
  Position left_end = {0, 4};
  Position right_end = {0, 0};
  ASSERT(contains_both_ends(left_end, right_end));
}

void horizontal_positions_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {4, 0};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_45_degree_slope_positions_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {3, 3};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_slope_greater_than_45_degrees_positions_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {3, 8};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_slope_less_than_45_degrees_positions_contain_both_ends()
{
  Position left_end = {0, 0};
  Position right_end = {8, 3};
  ASSERT(contains_both_ends(left_end, right_end));
}

void with_negative_slope_positions_contain_both_ends()
{
  Position left_end = {0, -3};
  Position right_end = {0, -8};
  ASSERT(contains_both_ends(left_end, right_end));
}

void run_all_tests()
{
  begin_group("line");
  test(vertical_positions_are_unique);
  test(horizontal_positions_are_unique);
  test(with_45_degree_slope_positions_are_unique);
  test(with_slope_greater_than_45_degrees_positions_are_unique);
  test(with_slope_less_than_45_degrees_positions_are_unique);
  test(with_negative_slope_positions_are_unique);

  test(vertical_positions_contain_both_ends);
  test(horizontal_positions_contain_both_ends);
  test(with_45_degree_slope_positions_contain_both_ends);
  test(with_slope_greater_than_45_degrees_positions_contain_both_ends);
  test(with_slope_less_than_45_degrees_positions_contain_both_ends);
  test(with_negative_slope_positions_contain_both_ends);
  end_group("line");
}
}  // namespace line

namespace rectangle
{
void positions_are_unique()
{
  Position top_left_corner = {10, 0};
  Position bottom_right_corner = {0, 10};

  std::list<Position> positions =
      Rectangle(top_left_corner, bottom_right_corner).positions();
  ASSERT(list_positions_are_unique(positions));
}

void run_all_tests()
{
  begin_group("rectangle");
  test(positions_are_unique);
  end_group("rectangle");
}
}  // namespace rectangle

}  // namespace shapes
void run_all_tests()
{
  begin_group("multiplayer_wireworld_shapes");
  shapes::rectangle::run_all_tests();
  shapes::line::run_all_tests();
  end_group("multiplayer_wireworld_shapes");
}
}  // namespace grid_shapes

