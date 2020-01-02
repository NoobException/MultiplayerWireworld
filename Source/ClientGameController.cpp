
#include "ClientGameController.hpp"

ClientGameController::ClientGameController(
    Game &game,
    ClientNetworkController &controller) : game(game),
                                           networkController(controller),
                                           gameRenderer(game, controller)
{
}

void ClientGameController::run()
{
    gameRenderer.run();
    /*
    while (gameRenderer.isRunning())
    {
        processWindowEvents();
        processNetworkEvents();
        displayCurrentMode();
        draw();
    }*/
}