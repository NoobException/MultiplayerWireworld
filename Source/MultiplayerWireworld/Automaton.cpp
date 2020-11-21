#include "MultiplayerWireworld/Automaton.hpp"

using namespace MultiplayerWireworld;

bool Cell::operator==(const Cell& rhs) const
{
  return type == rhs.type && position == rhs.position;
}

void Automaton::set_cells(const std::list<Cell>& cells_to_set)
{
  for (auto cell : cells_to_set) cells[cell.position] = cell;
}

std::list<Cell> Automaton::get_cells(const std::list<Position>& positions) const
{
  std::list<Cell> result;
  for (auto position : positions)
  {
    if (cells.contains(position))
      result.push_back(cells.at(position));
    else
      result.push_back({Cell::EMPTY, position});
  }
  return result;
}

void Automaton::advance()
{
  std::map<Position, Cell::Type> changes;
  for (auto [position, cell] : cells)
  {
    if (cell.type == Cell::EMPTY)
      continue;
    else if (cell.type == Cell::HEAD)
      changes[position] = Cell::TAIL;
    else if (cell.type == Cell::TAIL)
      changes[position] = Cell::CONDUCTOR;
    else  // CONDUCTOR
    {
      int heads = 0;
      for (auto neighbor : neighbors(position))
        if (cells[neighbor].type == Cell::HEAD) heads++;
      if (heads > 0 && heads < 3) changes[position] = Cell::HEAD;
    }
  }

  for (auto [position, type] : changes) cells[position].type = type;
}

std::list<Position> Automaton::neighbors(Position position)
{
  std::list<Position> result;
  for (int dx = -1; dx < 2; dx++)
    for (int dy = -1; dy < 2; dy++)
    {
      if (dx == 0 && dy == 0) continue;
      Position new_position = {position.x + dx, position.y + dy};
      if (!cells.contains(new_position)) continue;
      result.push_back(new_position);
    }
  return result;
}
