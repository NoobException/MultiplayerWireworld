#ifndef GAME_GRID_HPP
#define GAME_GRID_HPP

#include <memory>
#include <functional>

#include "Game/Cells.hpp"

namespace Game
{

class Grid
{
public:
    virtual bool is_on_grid(Cell::Coords&) const = 0;
    virtual void set_cell_state(Cell::Coords&, Cell::State&) = 0;
    virtual const Cell::State& get_cell_state(Cell::Coords&) const = 0; 
    
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual Cells get_changed_cells() = 0;
    virtual Cells get_all_cells() = 0;
};
} // namespace Game

#endif // GAME_GRID_HPP
