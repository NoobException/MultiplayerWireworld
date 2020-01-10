#include "Automata/Wireworld.hpp"

#include <memory>

using namespace std;
using namespace Automata;

WireworldState::WireworldState(Type type)
{
    this->type = type;
}

unique_ptr<Game::CellState> WireworldState::copy() const
{
    return unique_ptr<CellState>((CellState *)new WireworldState(type));
}

Wireworld::Wireworld(Game::Grid &grid) : grid(grid)
{
}

void Wireworld::update()
{
    unique_ptr<Game::Grid> grid_copy = grid.get_copy();
    grid.for_each_field([&grid_copy, this](const Game::CellCoords &coords) {
        grid.set_cell_state(coords, calculate_new_state(coords, *grid_copy));
    });
}

WireworldState &&Wireworld::calculate_new_state(const Game::CellCoords &coords, Game::Grid &grid_copy)
{
    WireworldState current_state = get_cell_state(coords, grid_copy);
    switch (current_state.type)
    {
    case WireworldState::EMPTY:
        return move(WireworldState(WireworldState::EMPTY));
    case WireworldState::HEAD:
        return move(WireworldState(WireworldState::HEAD));
    case WireworldState::TAIL:
        return move(WireworldState(WireworldState::COND));
    case WireworldState::COND:
        return calculate_conductor_state(coords, grid_copy);
    }
}

WireworldState &&Wireworld::calculate_conductor_state(const Game::CellCoords &coords, Game::Grid &grid_copy)
{
    int count = count_head_neighbors(coords, grid_copy);
    if (count == 0)
        return move(WireworldState(WireworldState::COND));
    else if (count <= 2)
        return move(WireworldState(WireworldState::HEAD));
    else
        return move(WireworldState(WireworldState::COND));
}

int Wireworld::count_head_neighbors(const Game::CellCoords &coords, Game::Grid &grid_copy)
{
    int count = 0;
    coords.for_each_neighbor([&grid_copy, &count, this](const Game::CellCoords &neighbor_coords) {
        if (grid_copy.is_on_grid(neighbor_coords))
        {
            WireworldState state = get_cell_state(neighbor_coords, grid_copy);
            if (state.type == WireworldState::HEAD)
                count++;
        }
    });
    return count;
}

WireworldState &&Wireworld::get_cell_state(const Game::CellCoords &coords, Game::Grid &grid_copy)
{
    return static_cast<WireworldState &&>(move(*grid_copy.get_cell_state(coords)));
}