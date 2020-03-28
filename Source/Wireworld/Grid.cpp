#include "Wireworld/Grid.hpp"

using namespace Wireworld;

Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Grid::get_width() const
{
    return width;
}

int Grid::get_height() const
{
    return height;
}

Game::Cells Grid::get_changed_cells()
{
    return Game::Cells{changed_cells};
}

Game::Cells Grid::get_all_cells()
{
    return Game::Cells{all_cells};
}

bool Grid::is_on_grid(Game::Cell::Coords&) const
{

}

void Grid::set_cell_state(
    Game::Cell::Coords& coords,
    Game::Cell::State& state)
{
}

const Game::Cell::State& Grid::get_cell_state(Game::Cell::Coords& coords) const 
{

}

Cell::Coords Grid::extract_coords(Game::Cell::Coords& coords)
{
    return static_cast<Cell::Coords&>(coords);
}

Cell::State Grid::extract_state(Game::Cell::State& state)
{
    return static_cast<Cell::State&>(state);
}

