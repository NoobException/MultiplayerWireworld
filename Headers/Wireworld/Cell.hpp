#ifndef WIREWORLD_CELL_HPP
#define WIREWORLD_CELL_HPP

#include "Game/Cell.hpp"

namespace Wireworld
{
struct Cell : public Game::Cell
{
    struct State : public Game::Cell::State
    {
        enum Type
        {
        };
        Type type;
    };

    struct Coords : public Game::Cell::Coords
    {
        int x, y;
    };

    State state;
    Coords coords;

    std::unique_ptr<Game::Cell> clone() override; 
};

} // namespace Wireworld

#endif // WIREWORLD_CELL_HPP
