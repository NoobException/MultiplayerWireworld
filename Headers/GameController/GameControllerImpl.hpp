#ifndef GAMECONTROLLER_GAMECONTROLLERIMPL_HPP
#define GAMECONTROLLER_GAMECONTROLLERIMPL_HPP

#include <memory>
#include "GameController/GameController.hpp"
#include "Game/GameLogic.hpp"

using namespace std;
namespace GameController
{
class GameControllerImpl : GameController
{
public:
    GameControllerImpl(Game::GameLogic &);
    virtual unique_ptr<Game::CellState> get_cell_state(const Game::CellCoords &) override;
    virtual void update_automaton() override;
    virtual void set_custom_shape(const Game::Shape &, const Game::CellState &) override;

private:
    Game::GameLogic &game_logic;
};
} // namespace GameController

#endif // GAMECONTROLLER_GAMECONTROLLERIMPL_HPP