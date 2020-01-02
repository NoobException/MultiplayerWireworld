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
    void setCell(int x, int y, State state);
    void setLine(int x1, int y1, int x2, int y2, State state);
    void setRectangle(int x1, int y1, int x2, int y2, State state);
    Game(int width, int height);

private:
    WireworldGrid grid;
    WireworldGrid ghosts;
};

#endif // GAME_H
