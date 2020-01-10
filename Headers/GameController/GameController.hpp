#ifndef GAMECONTROLLER_GAMECONTROLLER_HPP
#define GAMECONTROLLER_GAMECONTROLLER_HPP

#include "Game/GameLogic.hpp"
#include "GameController/UIController.hpp"
#include "GameController/NetworkController.hpp"

namespace GameController
{
class GameController : public UIController, public NetworkController
{
public:
private:
    GameLogic &game_logic;
};
}

#endif // !GAMECONTROLLER_GAMECONTROLLER_HPP