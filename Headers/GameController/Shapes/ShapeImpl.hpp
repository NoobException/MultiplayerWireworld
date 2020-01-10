#ifndef GAMECONTROLLER_SHAPES_CELLIMPL_HPP
#define GAMECONTROLLER_SHAPES_CELLIMPL_HPP

#include <vector>
#include <memory>

#include "Game/Shape.hpp"
#include "Game/CellCoords.hpp"

using namespace std;

typedef vector<shared_ptr<Game::CellCoords>>::const_iterator ShapeIterator;

namespace GameController
{
class ShapeImpl : public Game::Shape
{
public:
    virtual ShapeIterator begin() const override;
    virtual ShapeIterator end() const override;

private:
    vector<shared_ptr<Game::CellCoords>> shape;
};
} // namespace GameController

#endif //  GAMECONTROLLER_SHAPES_CELLIMPL_HPP