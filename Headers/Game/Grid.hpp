#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <memory>
#include <exception>
#include <functional>

#include "Game/CellState.hpp"
#include "Game/CellCoords.hpp"

using namespace std;

namespace Game
{
class GridException : exception
{
};

class Grid
{
public:
    virtual void set_cell_state(const CellCoords &, const CellState &) = 0;
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &) const = 0;
    virtual bool is_on_grid(const CellCoords &) const = 0;

    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual unique_ptr<Grid> get_copy() const = 0;
    virtual void set_grid(const Grid &) = 0;

    virtual void for_each_field(function<void(const CellCoords &)>) const = 0;
};
} // namespace Game

#endif // GAME_GRID_HPP