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

public:
    Game();

private:
    WireworldGrid grid;
};

#endif // GAME_H
