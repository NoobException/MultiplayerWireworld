#ifndef CLIENT_GAME_CONTROLLER_HPP
#define CLIENT_GAME_CONTROLLER_HPP

#include "Networking/ClientNetworkController.hpp"
#include "GameRenderer.hpp"

class ClientGameController
{
public:
    ClientGameController(Game &game, ClientNetworkController &controller);
    void run();

private:
    Game &game;
    ClientNetworkController &networkController;
    GameRenderer gameRenderer;
};

#endif //CLIENT_GAME_CONTROLLER_HPP