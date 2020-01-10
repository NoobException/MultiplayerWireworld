#ifndef CELL_COORDS_HPP
#define CELL_COORDS_HPP

#include <functional>

using namespace std;

namespace Game
{
class CellCoords
{
public:
    virtual void for_each_neighbor(function<void(const CellCoords &)>) const = 0;
};
} // namespace Game

#endif