
#include "ServerGameController.hpp"

ServerGameController::ServerGameController(
    Game &game,
    ServerNetworkController &networkController) : game(game), 
    networkController(networkController)
{}
void ServerGameController::run()
{
    while (true)
    {
        while (networkController.hasNextEvent())
        {
            NetworkEvent *event = networkController.getNextEvent();
            networkController.gameMutex.lock();
            event->apply(game);
            networkController.gameMutex.unlock();
        }
    }
}