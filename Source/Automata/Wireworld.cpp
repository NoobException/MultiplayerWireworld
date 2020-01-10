#include "Automata/Wireworld.hpp"

using namespace Automata;

Wireworld::Wireworld(Game::Grid &grid) : grid(grid)
{
}

void Wireworld::update()
{
    unique_ptr<Game::Grid> grid_copy = grid.get_copy();
    for (int x = 0; x < grid.get_width(); x++)
    {
        for (int y = 0; y < grid.get_height(); y++)
        {
            Game::CellCoords cords = Game::CellCoords(x, y);
            calculateNewState();
        }
    }
}

WireworldState Wireworld::calculateNewState(const Game::CellCoords &coords)
{
    WireworldState current_state, new_state;
    switch (current_state)
    {
    case WireworldState::EMPTY:
        new_state = WireworldState::EMPTY;
        break;
    case WireworldState::HEAD:
        new_state = WireworldState::TAIL;
        break;
    case WireworldState::TAIL:
        new_state = WireworldState::COND;
        break;
    case WireworldState::COND:
        new_state = calculateConductorState(coords);
        break;
    }
}

WireworldState Wireworld::calculateConductorState(const Game::CellCoords &coords)
{
    int n = 0;
    for (int dx = -1; dx < 2; dx++)
        for (int dy = -1; dy < 2; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                continue;

            if (getCell(nx, ny) == WireworldState::HEAD)
                n++;
        }
    new_state = (n == 1 || n == 2 ? WireworldState::HEAD : WireworldState::COND);
    return new_state;
}