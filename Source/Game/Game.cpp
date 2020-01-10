
#include "Game.hpp"
#include "Utils.hpp"
Game::Game(int width, int height)
{
}

/*
void setLine(int x1, int y1, int x2, int y2, std::unique_ptr<CellState> state)
{
    std::vector<sf::Vector2i> points = getLine(x1, y1, x2, y2);
    for (sf::Vector2i point : points)
    {
        grid->set_cell(point.x, point.y, state);
    }
}
void setRectangle(int x1, int y1, int x2, int y2, std::unique_ptr<CellState> state)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            grid->set_cell(x, y, state);
}


void Game::clearWires()
{

    for (int x = 0; x < grid->get_width(); x++)
        for (int y = 0; y < grid->get_height(); y++)
        {
            if (grid.getCell(x, y) == State::HEAD || grid.getCell(x, y) == State::TAIL)
            {
                grid.setCell(x, y, State::COND);
            }
        }
        
}
*/