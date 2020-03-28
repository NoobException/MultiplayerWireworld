#ifndef GAME_CELL_HPP
#define GAME_CELL_HPP

#include <memory>

namespace Game
{
struct Cell
{
    struct State{};
    struct Coords{};
    virtual std::unique_ptr<Cell> clone() = 0;
};
} // namespace Game

#endif // GAME_CELL_HPP
