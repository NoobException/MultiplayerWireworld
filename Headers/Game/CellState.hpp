#ifndef GAME_CELLSTATE_HPP
#define GAME_CELLSTATE_HPP

#include <memory>

using namespace std;

namespace Game
{
class CellState
{
public:
    virtual unique_ptr<CellState> copy() const = 0;
};
} // namespace Game

#endif //GAME_CELLSTATE_HPP