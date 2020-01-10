#ifndef GAME_SHAPE_HPP
#define GAME_SHAPE_HPP

#include <iterator>
#include <memory>

#include "Game/CellCoords.hpp"

typedef iterator<shared_ptr<Game::CellCoords>> ShapeIterator;

namespace Game
{
class Shape
{
public:
    virtual ShapeIterator begin() const = 0;
    virtual ShapeIterator end() const = 0;
};
} // namespace Game

#endif // GAME_SHAPE_HPP