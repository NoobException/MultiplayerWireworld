
#include "ServerGameController.hpp"

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