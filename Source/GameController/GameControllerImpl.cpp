#include "GameController/GameControllerImpl.hpp"
#include "Game/GameLogic.hpp"
#include "GameController/ComponentController.hpp"

using namespace GameController;

GameControllerImpl::GameControllerImpl(
    Game::GameLogic &game_logic,
    ComponentController &ui_controller,
    ComponentController &network_controller)
    : game_logic(game_logic),
      ui_controller(ui_controller),
      network_controller(network_controller)
{
}

unique_ptr<Game::CellState> GameControllerImpl::get_cell_state(const Game::CellCoords &) {}
void GameControllerImpl::update_automaton() {}
void GameControllerImpl::set_custom_shape(const Game::Shape &, const Game::CellState &) {}

void GameControllerImpl::start()
{
    while (game_logic.is_running())
    {
        game_logic.update();
    }
}