#ifndef GAME_H
#define GAME_H

#include "WireworldGrid.hpp"

class Game
{
    friend class GameRenderer;
    friend class ServerNetworkController;
    friend class NewPlayerEvent;
    friend class CellChangedEvent;
    friend class AdvanceSimulationEvent;
    friend class RectangleChangedEvent;
    friend class LineChangedEvent;

public:
    Game(int width, int height);

private:
    WireworldGrid grid;
    WireworldGrid ghosts;
};

#endif // GAME_H
