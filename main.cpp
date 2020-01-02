
#include "GameRenderer.hpp"
#include "ServerNetworkController.hpp"
#include "ClientNetworkController.hpp"

#define CLIENT
int main()
{
#ifdef SERVER
    Game game(64, 64);
    ServerNetworkController controller(25565, game);
    while (true)
    {
        while (controller.hasNextEvent())
        {
            NetworkEvent *event = controller.getNextEvent();
            controller.gameMutex.lock();
            event->apply(game);
            controller.gameMutex.unlock();
        }
    }
#else
    Game game(64, 64);
    sf::IpAddress addr("retardcraft.ddns.net");
    ClientNetworkController controller(addr, 25565);
    GameRenderer renderer(game, controller);
    renderer.run();
    controller.stop();
#endif
}