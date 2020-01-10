#ifndef AUTOMATA_WIREWORLD_HPP
#define AUTOMATA_WIREWORLD_HPP

#include "Game/Automaton.hpp"
#include "Game/CellState.hpp"
#include "Game/Grid.hpp"
#include "Game/CellCoords.hpp"

namespace Automata
{
class WireworldState : Game::CellState
{
    enum Type
    {
        NONE,
        EMPTY,
        HEAD,
        TAIL,
        COND
    };
};

class Wireworld : Game::Automaton
{
public:
    Wireworld(Game::Grid &);
    virtual void update() override;

private:
    WireworldState calculateNewState(const Game::CellCoords &);
    WireworldState calculateConductorState(const Game::CellCoords &);
    Game::Grid &grid;
};
} // namespace Automata

#endif // AUTOMATA_WIREWORLD_HPP