#ifndef CELL_COORDS_HPP
#define CELL_COORDS_HPP
namespace Game
{
class CellCoords
{
public:
    CellCoords(const CellCoords &) = default;
    virtual CellCoords &operator=(const CellCoords &);
};
} // namespace Game

#endif