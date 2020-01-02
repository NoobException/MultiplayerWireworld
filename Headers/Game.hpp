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
    Game();

private:
    WireworldGrid grid;
};

#endif // GAME_H
