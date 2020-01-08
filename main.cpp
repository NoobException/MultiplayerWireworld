
#include <iostream>

#include "Networking/ServerNetworkController.hpp"
#include "Networking/ClientNetworkController.hpp"

#include "ClientGameController.hpp"
#include "ServerGameController.hpp"

#include "Game.hpp"

#define CLIENT
int main()
{
    Game game(64, 64);
#ifdef SERVER
    ServerNetworkController networkController(25565, game);
    ServerGameController gameController(game, networkController);
#else
    std::string address;
    std::cin >> address;
    sf::IpAddress addr(address);
    ClientNetworkController networkController(addr, 25565);
    ClientGameController gameController(game, networkController);
#endif

    gameController.run();
    networkController.stop();
}