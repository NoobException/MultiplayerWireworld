#include "Game/GameLogicImpl.hpp"

using namespace std;
using namespace Game;

GameLogicImpl::GameLogicImpl(GamePresenter &game_presenter, Grid &grid, Automaton &automaton) : game_presenter(game_presenter), grid(grid), automaton(automaton)
{
}

unique_ptr<CellState> GameLogicImpl::get_cell_state(const CellCoords &cell_coords)
{
    return grid.get_cell_state(cell_coords);
}

void GameLogicImpl::update_automaton()
{
    automaton.update();
}

void GameLogicImpl::set_custom_shape(const Shape &shape, const CellState &cell_state)
{
    for (const auto &cell_coords : shape)
    {
        grid.set_cell_state(*cell_coords, cell_state);
    }
}

