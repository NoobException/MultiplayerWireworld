#ifndef GRIDCONTROLLER_HPP
#define GRIDCONTROLLER_HPP

#include <memory>
#include "Grid.hpp"

class GridController
{
public:
    virtual void set_cell(int x, int y, std::unique_ptr<CellState> state);
    virtual CellState get_cell(int x, int y);
    virtual bool is_on_grid(int x, int y);
    virtual int get_width();
    virtual int get_height();
};


#endif // GRIDCONTROLLER_HPP


