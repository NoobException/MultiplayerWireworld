#include "GameController/Shapes/ShapeImpl.hpp"

using namespace GameController;

typedef vector<shared_ptr<CellCoords>>::const_iterator ShapeIterator;

ShapeIterator ShapeImpl::begin() const
{
    return shape.begin();
}

ShapeIterator ShapeImpl::end() const
{
    return shape.end();
}