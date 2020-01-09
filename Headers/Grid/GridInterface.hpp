#ifndef GRIDINTERFACE_HPP
#define GRIDINTERFACE_HPP

#include <stdexcept>
#include <memory>

#include "CellState.hpp"

enum class State 
{
    EMPTY,
    COND,
    TAIL,
    HEAD,
    NONE
};


class GridException : std::exception
{};

class GridInterface
{
public:
    GridInterface(){};
    virtual ~GridInterface(){};

    virtual void update() = 0;
    virtual void set_cell(int x, int y, std::unique_ptr<CellState> state) = 0;
    virtual std::unique_ptr<CellState> get_cell(int x, int y) = 0;
    virtual bool is_on_grid(int x, int y) = 0;

    virtual int get_width() = 0;
    virtual int get_height() = 0;
};

#endif
