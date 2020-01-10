#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <memory>
#include <exception>

#include "Game/CellState.hpp"

using namespace std;

namespace Game
{
class GridException : exception
{
};

class Grid
{
public:
    virtual void set_cell_state(const CellCoords &, const CellState &);
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &);
    virtual bool is_on_grid(const CellCoords &);

    virtual int get_width();
    virtual int get_height();

    virtual unique_ptr<Grid> get_copy();
    virtual void set_grid(const Grid &);
};
} // namespace Game

#endif // GAME_GRID_HPP