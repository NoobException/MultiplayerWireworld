#include "Grid/CellCoordsImpl.hpp"

using namespace Grid;

CellCoordsImpl::CellCoordsImpl(int x, int y)
{
    this->x = x;
    this->y = y;
}

void CellCoordsImpl::for_each_neighbor(function<void(const CellCoords &)> f) const
{
    for (int nx = x - 1; nx <= x + 1; nx++)
        for (int ny = y - 1; ny <= y + 1; ny++)
            if (nx != x && ny != y)
                f(CellCoordsImpl(nx, ny));
}