#ifndef GAMECONTROLLER_GAMECONTROLLERIMPL_HPP
#define GAMECONTROLLER_GAMECONTROLLERIMPL_HPP

#include <memory>
#include "GameController/GameController.hpp"
#include "Game/GameLogic.hpp"
#include "GameController/UIController.hpp"
#include "GameController/NetworkController.hpp"

using namespace std;
namespace GameController
{
class GameControllerImpl : public GameController
{
public:
    GameControllerImpl(Game::GameLogic &, ComponentController &, ComponentController &);
    virtual unique_ptr<Game::CellState> get_cell_state(const Game::CellCoords &) override;
    virtual void update_automaton() override;
    virtual void set_custom_shape(const Game::Shape &, const Game::CellState &) override;
    virtual void start() override;

private:
    Game::GameLogic &game_logic;
    ComponentController &ui_controller;
    ComponentController &network_controller;
};
} // namespace GameController

#endif // GAMECONTROLLER_GAMECONTROLLERIMPL_HPP