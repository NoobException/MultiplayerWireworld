#ifndef GAME_SHAPE_HPP
#define GAME_SHAPE_HPP

#include <iterator>
#include <vector>

#include "Game/CellCoords.hpp"

using namespace std;

typedef vector<unique_ptr<Game::CellCoords>>::const_iterator ShapeIterator;

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