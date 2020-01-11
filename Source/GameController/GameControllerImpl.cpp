#include "GameController/GameControllerImpl.hpp"
#include "Game/GameLogic.hpp"

using namespace GameController;

GameControllerImpl::GameControllerImpl(Game::GameLogic &game_logic)
    : game_logic(game_logic)
{
}

unique_ptr<Game::CellState> GameControllerImpl::get_cell_state(const Game::CellCoords &) {}
void GameControllerImpl::update_automaton() {}
void GameControllerImpl::set_custom_shape(const Game::Shape &, const Game::CellState &) {}