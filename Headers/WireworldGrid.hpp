#ifndef WIREWORLDGRID_HPP
#define WIREWORLDGRID_HPP

#include <stdexcept>

#include "GridInterface.hpp"
class WireworldGrid
{
public:
    WireworldGrid(int width, int height);
    WireworldGrid(const WireworldGrid &other);
    virtual ~WireworldGrid();

    const WireworldGrid &operator=(const WireworldGrid &);

    virtual void update();

    virtual void setCell(int x, int y, State state);
    void setLine(int x1, int y1, int x2, int y2, State state);
    void setRectangle(int x1, int y1, int x2, int y2, State state);
    virtual State getCell(int x, int y);
    bool isOnGrid(int x, int y);
    int getWidth();
    int getHeight();

private:
    State *grid;

    virtual void createGrid(int width, int height);
    virtual void freeGrid();

    int width;
    int height;
};

#endif
