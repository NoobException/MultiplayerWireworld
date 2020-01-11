#ifndef GAMECONTROLLER_GAMECONTROLLER_HPP
#define GAMECONTROLLER_GAMECONTROLLER_HPP

#include "Game/GameLogic.hpp"

namespace GameController
{
class GameController
{
public:
    virtual unique_ptr<Game::CellState> get_cell_state(const Game::CellCoords &) = 0;
    virtual void update_automaton() = 0;
    virtual void set_custom_shape(const Game::Shape &, const Game::CellState &) = 0;
};
} // namespace GameController

#endif // GAMECONTROLLER_GAMECONTROLLER_HPP