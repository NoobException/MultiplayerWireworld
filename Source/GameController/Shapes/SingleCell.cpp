#include "GameController/Shapes/SingleCell.hpp"

using namespace std;
using namespace GameController;

SingleCell::SingleCell(const CellCoords &cell_coords)
{
    coords = make_unique<CellCoords>(new CellCoords(cell_coords));
    shape.push_back(make_shared<CellCoords>(new CellCoords(cell_coords)));
}
