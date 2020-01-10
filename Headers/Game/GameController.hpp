#ifndef GAME_GAMECONTROLLER_HPP
#define GAME_GAMECONTROLLER_HPP

#include <vector>

#include "Game/CellState.hpp"
#include "Game/CellCoords.hpp"

using namespace std;
namespace Game
{

class GameController
{
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &) = 0;
    virtual void update_automaton() = 0;
    virtual void set_custom_shape(const Shape &, const CellState &) = 0;
};
} // namespace Game

#endif //  GAMECONTROLLER_HPP