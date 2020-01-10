#ifndef GAME_CELLSTATE_HPP
#define GAME_CELLSTATE_HPP

namespace Game
{
class CellState
{
};
} // namespace Game

#endif

// Network -> (Event) -> Controller.set_cell() -> GridInterface.set_cell() -> Grid.set_cell(x, y, CellState)