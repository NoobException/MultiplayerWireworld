#ifndef WIREWORLD_CELL_HPP
#define WIREWORLD_CELL_HPP

#include <memory>

#include "Game/Cell.hpp"

namespace Wireworld
{
struct Cell : public Game::Cell
{
    struct State : public Game::Cell::State
    {
        enum Type
        {
            Empty,
            Head,
            Tail, 
            Conductor,
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
    
    static Cell from_unique_ptr(std::unique_ptr<Game::Cell>);
};

} // namespace Wireworld

#endif // WIREWORLD_CELL_HPP
