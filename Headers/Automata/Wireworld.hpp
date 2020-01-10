#ifndef AUTOMATA_WIREWORLD_HPP
#define AUTOMATA_WIREWORLD_HPP

#include "Game/Automaton.hpp"
#include "Game/CellState.hpp"
#include "Game/Grid.hpp"
#include "Game/CellCoords.hpp"

namespace Automata
{
class WireworldState : public Game::CellState
{
public:
    enum Type
    {
        NONE,
        EMPTY,
        HEAD,
        TAIL,
        COND
    };
    WireworldState(Type type);
    Type type;
};

class Wireworld : public Game::Automaton
{
public:
    Wireworld(Game::Grid &);
    virtual void update() override;

private:
    WireworldState &&calculate_new_state(const Game::CellCoords &, Game::Grid &);
    WireworldState &&calculate_conductor_state(const Game::CellCoords &, Game::Grid &);
    int count_head_neighbors(const Game::CellCoords &, Game::Grid &);
    Game::Grid &grid;

    WireworldState &&get_cell_state(const Game::CellCoords &coords, Game::Grid &grid_copy);
};
} // namespace Automata

#endif // AUTOMATA_WIREWORLD_HPP