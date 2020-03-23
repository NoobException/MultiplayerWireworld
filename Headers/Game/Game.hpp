// Boundary interface for sending information into the Game

#ifndef GAME_GAMELOGIC_HPP
#define GAME_GAMELOGIC_HPP

#include <memory>

#include "Game/CellCoords.hpp"
#include "Game/CellState.hpp"
#include "Game/Shape.hpp"

namespace Game
{
class Game
{
public:
    virtual bool is_running() = 0;
    virtual std::unique_ptr<CellState> get_cell_state(const CellCoords &) = 0;
    virtual void set_custom_shape(const Shape &, const CellState &) = 0;
    virtual void update() = 0;
    virtual void update_automaton() = 0;
    virtual void start() = 0;
    virtual void quit() = 0;
};
} // namespace Game

#endif // GAME_GAMELOGIC_HPP