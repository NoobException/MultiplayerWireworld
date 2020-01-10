#ifndef GRID_CELLCOORDSIMPL_HPP
#define GRID_CELLCOORDSIMPL_HPP
#include "Game/CellCoords.hpp"

using namespace std;

namespace Grid
{
class CellCoordsImpl : public Game::CellCoords
{
public:
    CellCoordsImpl(int x, int y);
    virtual void for_each_neighbor(function<void(const CellCoords &)>) const override;

private:
    int x, y;
};
} // namespace Grid
#endif //GRID_CELLCOORDSIMPL_HPP
