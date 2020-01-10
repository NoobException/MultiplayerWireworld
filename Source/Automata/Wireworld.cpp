#include "Automata/Wireworld.hpp"

#include <memory>

using namespace std;
using namespace Automata;

Wireworld::Wireworld(Game::Grid &grid) : grid(grid)
{
}

void Wireworld::update()
{
    unique_ptr<Game::Grid> grid_copy = grid.get_copy();
    grid.for_each_field([&grid_copy, this](const Game::CellCoords &coords) {
        grid.set_cell_state(coords, make_unique(calculate_new_state(coords)));
    });
}

WireworldState Wireworld::calculate_new_state(const Game::CellCoords &coords, Game::Grid &grid_copy)
{
    WireworldState current_state = static_cast<WireworldState &&>(grid_copy.get_cell_state(coords));
    switch (current_state.type)
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