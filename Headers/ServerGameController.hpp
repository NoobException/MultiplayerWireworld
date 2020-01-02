#ifndef SERVERGAMECONTROLLER_HPP
#define SERVERGAMECONTROLLER_HPP

#include "Networking/ServerNetworkController.hpp"

class ServerGameController
{
public:
    ServerGameController(Game &game, ServerNetworkController &controller);
    void run();

private:
    Game &game;
    ServerNetworkController &networkController;
};

#endif //CLIENT_GAME_CONTROLLER_HPP