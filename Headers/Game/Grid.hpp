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
    virtual void set_cell_state(const CellCoords &, unique_ptr<CellState>);
    virtual CellState &&get_cell_state(const CellCoords &);
    virtual bool is_on_grid(const CellCoords &);

    virtual int get_width();
    virtual int get_height();

    virtual unique_ptr<Grid> get_copy();
    virtual void set_grid(const Grid &);

    virtual void for_each_field(function<void(const CellCoords &)>);
};
} // namespace Game

#endif // GAME_GRID_HPP