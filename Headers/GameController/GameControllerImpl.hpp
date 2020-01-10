#ifndef GAMECONTROLLER_GAMECONTROLLERIMPL_HPP
#define GAMECONTROLLER_GAMECONTROLLERIMPL_HPP

#include <memory>

#include "Game/GameController.hpp"

using namespace std;
namespace GameController
{

class GameControllerImpl : GameController
{
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &) override;
    virtual void update_automaton() override;
    virtual void set_custom_shape(const Shape &, const CellState &) override;
};
} // namespace Game

#endif // GAMECONTROLLER_GAMECONTROLLERIMPL_HPP