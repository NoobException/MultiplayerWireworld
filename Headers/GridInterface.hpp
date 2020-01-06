#ifndef GRIDINTERFACE_HPP
#define GRIDINTERFACE_HPP

#include <stdexcept>

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
    virtual void setCell(int x, int y, State state) = 0;
    virtual State getCell(int x, int y) = 0;

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};

#endif
