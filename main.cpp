
#include "GameRenderer.hpp"
#include "ServerNetworkController.hpp"
int main()
{
#ifdef SERVER
    Game game;
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
    Game game;
    GameRenderer renderer(game);
    renderer.run();
#endif
}