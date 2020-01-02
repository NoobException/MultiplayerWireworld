
#include "Game.hpp"

Game::Game(int width, int height) : grid(width, height), ghosts(width, height)
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            ghosts.setCell(x, y, State::NONE);
        }
}