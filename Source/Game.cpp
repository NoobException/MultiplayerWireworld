
#include "Game.hpp"
#include "Utils.hpp"
Game::Game(int width, int height) : grid(width, height), ghosts(width, height)
{
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            ghosts.setCell(x, y, State::NONE);
        }
}
void Game::setCell(int x, int y, State state)
{
    grid.setCell(x, y, state);
    ghosts.setCell(x, y, State::NONE);
}
void Game::setLine(int x1, int y1, int x2, int y2, State state)
{
    std::vector<sf::Vector2i> points = getLine(x1, y1, x2, y2);
    for (sf::Vector2i point : points)
    {
        setCell(point.x, point.y, state);
    }
}
void Game::setRectangle(int x1, int y1, int x2, int y2, State state)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            setCell(x, y, state);
}