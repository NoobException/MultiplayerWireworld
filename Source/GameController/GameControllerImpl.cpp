#include "GameController/GameControllerImpl.hpp"
#include "Game/GameLogic.hpp"

using namespace GameController;

GameControllerImpl::GameControllerImpl(Game::GameLogic &game_logic) 
: game_logic(game_logic)
{
    
}