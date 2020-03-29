#include <string>

#include "Wireworld/Grid.hpp"
#include "Wireworld/Cells.hpp"

using namespace Wireworld;

Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;
    create_grid();
}

void Grid::create_grid()
{
    all_cells.resize(width * height);
    for (int i = 0; i < width * height; i++)
    {
        int x = i % width;
        int y = i / height;
        
        Cell &cell = all_cells[i];
        cell.coords.x = x;
        cell.coords.y = y;
        cell.state.type = Cell::State::Empty;
    }
};

int Grid::get_width() const
{
    return width;
}

int Grid::get_height() const
{
    return height;
}

std::unique_ptr<Game::Cells> Grid::get_changed_cells()
{
    return std::make_unique<Cells>(changed_cells);
}

std::unique_ptr<Game::Cells> Grid::get_all_cells()
{
    return std::make_unique<Cells>(all_cells);
}

void Grid::set_cells(std::unique_ptr<Game::Cells> game_cells)
{
    Cells cells = Cells::from_game_cells(move(game_cells));  
    for (Cell cell : cells)
    {
        int index = cell.coords.x + cell.coords.y * width;
        if (cell.coords.x > width || cell.coords.y > height)
            throw CoordsNotOnGrid(cell.coords);
        else
            all_cells[index] = cell;
    }
}

bool Grid::is_on_grid(Game::Cell::Coords&) const
{

}

void Grid::set_cell_state(
    Game::Cell::Coords& game_coords,
    Game::Cell::State& game_state)
{
    Cell::Coords coords = extract_coords(game_coords);
    Cell::State state = extract_state(game_state);
    int index = coords.x + coords.y * width;
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

CoordsNotOnGrid::CoordsNotOnGrid(Cell::Coords)
{
    this->coords = coords;
}


const char *CoordsNotOnGrid::what() const noexcept
{
    const std::string result = "Given coordinates (" 
        + std::to_string(coords.x) + ", " + std::to_string(coords.y) + ")" +
        " are not valid.";
    return result.c_str();
}

