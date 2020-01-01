#ifndef GAME_H
#define GAME_H

#include "WireworldGrid.hpp"

class Game
{
friend class GameRenderer;
public:
    Game();
private:
    WireworldGrid grid;
};

#endif // GAME_H
