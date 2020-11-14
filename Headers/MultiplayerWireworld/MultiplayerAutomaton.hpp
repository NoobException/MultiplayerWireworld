#ifndef MULTIPLAYER_AUTOMATON
#define MULTIPLAYER_AUTOMATON

#include <memory>

#include "Automaton.hpp"
#include "WireworldNetwork.hpp"

namespace MultiplayerWireworld
{
struct MultiplayerCell
{
  Cell cell;
  bool is_ghost;
  bool operator==(const MultiplayerCell &) const;
};

class Shape
{
public:
  enum Type
  {
    SINGLE_CELL,
    RECTANGLE,
    LINE
  };
  virtual std::list<Cell> get_cells() const = 0;
  virtual Type type() const = 0;
  virtual ~Shape() = default;
};

class MultiplayerAutomaton
{
public:
  void set_shape(std::unique_ptr<Shape>);
  void set_cells(const std::list<Cell> &);
  void advance();
  std::list<MultiplayerCell> get_cells(const std::list<Position> &) const;

private:
  std::unique_ptr<WireworldNetwork> wireworld_network;
  Automaton automaton;
};
}  // namespace MultiplayerWireworld
#endif
