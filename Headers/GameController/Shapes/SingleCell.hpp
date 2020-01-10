#ifndef GAMECONTROLLER_SHAPES_SINGLECELL_HPP
#define GAMECONTROLLER_SHAPES_SINGLECELL_HPP

#include <vector>
#include <memory>

#include "GameController/Shapes/ShapeImpl.hpp"

#include "Game/CellCoords.hpp"

using namespace std;

namespace GameController
{
class SingleCell : public ShapeImpl
{
public:
    SingleCell(const CellCoords &);

private:
    unique_ptr<CellCoords> coords;
    vector<shared_ptr<CellCoords>> shape;
};
} // namespace GameController

#endif //  GAMECONTROLLER_SHAPES_SINGLECELL_HPP