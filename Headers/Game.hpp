#ifndef GAME_H
#define GAME_H

#include <memory>
#include "GridInterface.hpp"
#include "GridController.hpp"

class Game
{
    friend class ClientGameController;
    friend class GameRenderer;
    friend class DrawingController;
    friend class ServerNetworkController;
    friend class NewPlayerEvent;
    friend class CellChangedEvent;
    friend class AdvanceSimulationEvent;
    friend class RectangleChangedEvent;
    friend class LineChangedEvent;

public:
    void clearWires();
    Game(int width, int height);
    
    std::unique_ptr<GridController> grid_controller;
    std::unique_ptr<GridController> ghosts_controller;

private:
    std::unique_ptr<GridInterface> grid;
    std::unique_ptr<GridInterface> ghosts;
};

#endif // GAME_H
