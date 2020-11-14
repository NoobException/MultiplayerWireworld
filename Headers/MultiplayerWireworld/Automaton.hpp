#ifndef MULTIPLAYER_WIREWORLD_HPP
#define MULTIPLAYER_WIREWORLD_HPP

#include <list>
#include <map>

namespace MultiplayerWireworld
{
struct Position
{
  int x, y;
  bool operator==(const Position& rhs) const;
  bool operator<(const Position& rhs) const;
};

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

}  // namespace MultiplayerWireworld

#endif
