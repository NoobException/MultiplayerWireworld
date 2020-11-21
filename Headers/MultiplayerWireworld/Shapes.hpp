#ifndef MULTIPLAYER_WIREWORLD_SHAPES
#define MULTIPLAYER_WIREWORLD_SHAPES

#include <memory>

#include "Grid/Shapes.hpp"
#include "MultiplayerWireworld/Automaton.hpp"

namespace MultiplayerWireworld
{
struct CellShape
{
  Cell cell;
  std::unique_ptr<Grid::Shape> shape;
  std::list<Cell> cells() const
  {
    Cell copy = cell;
    std::list<Cell> result;
    for (auto position : shape->positions())
    {
      copy.position = position;
      result.push_back(copy);
    }
    return result;
  }
};
}  // namespace MultiplayerWireworld

#endif
