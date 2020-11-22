#ifndef MULTIPLAYER_WIREWORLD_AUTOMATON_HPP
#define MULTIPLAYER_WIREWORLD_AUTOMATON_HPP

#include <list>
#include <map>
#include <string>

#include "Grid/Grid.hpp"

namespace MultiplayerWireworld
{
struct Cell
{
  enum Type
  {
    EMPTY,
    HEAD,
    TAIL,
    CONDUCTOR,
  } type;

  Position position;

  bool operator==(const Cell& rhs) const;
};

class Automaton
{
  std::map<Position, Cell> cells;

public:
  void set_cells(const std::list<Cell>&);
  std::list<Cell> get_cells(const std::list<Position>&) const;
  void advance();

private:
  std::list<Position> neighbors(Position);
};

std::string cell_type_to_string(Cell::Type type);

}  // namespace MultiplayerWireworld

#endif
