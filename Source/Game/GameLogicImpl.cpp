#include "Game/GameLogic.hpp"
#include "Game/Shape.hpp"

using namespace std;
using namespace Game;

GameLogic::GameLogic(GamePresenter &game_presenter, Grid &grid, Automaton &automaton) : game_presenter(game_presenter), grid(grid), automaton(automaton)
{
}

unique_ptr<CellState> GameLogic::get_cell_state(const CellCoords &cell_coords)
{
    return grid.get_cell_state(cell_coords)
}

void GameLogic::update_automaton()
{
    automaton.update();
}

void GameLogic::set_custom_shape(const Shape &shape, const CellState &cell_state)
{
    for (const auto &cell_coords : shape)
    {
        grid.set_cell_state(*cell_coords, cell_state);
    }
}