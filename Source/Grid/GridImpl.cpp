#include "Grid/GridImpl.hpp"

using namespace std;
using namespace Grid;

InvalidGridDimensionsException::InvalidGridDimensionsException(int width, int height) : width(width), height(height)
{
}

const char *InvalidGridDimensionsException::what() const noexcept
{
    const std::string errorMessage = "Cannot create a grid of size " + std::to_string(width) + " x " + std::to_string(height);
    return errorMessage.c_str();
}

InvalidGridCoordinatesException::InvalidGridCoordinatesException(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{
}

const char *InvalidGridCoordinatesException::what() const noexcept
{
    const std::string errorMessage = "Cordinates (" + std::to_string(x) + ", " + std::to_string(y) + ") are not valid on a grid of size " + std::to_string(width) + " x " + std::to_string(height);
    return errorMessage.c_str();
}

GridImpl::GridImpl(int width, int height)
{
    create_grid(width, height);
}

void GridImpl::set_cell_state(const Game::CellCoords &coords, unique_ptr<Game::CellState> state)
{
    if (!is_on_grid(coords))
        throw InvalidGridCoordinatesException(x, y, width, height);
    grid[y * width + x] = state;
}

Game::CellState &&GridImpl::get_cell_state(const Game::CellCoords &coords)
{
    if (!is_on_grid(coords))
        throw InvalidGridCoordinatesException(x, y, width, height);

    return *grid[y * width + x];
}

void GridImpl::create_grid(int width, int height)
{
    this->width = width;
    this->height = height;
    grid = std::make_unique<Game::CellState>(new Game::CellState[width * height]);
}

bool GridImpl::is_on_grid(const Game::CellCoords &)
{
    return (x >= 0 && x < width && y >= 0 && y < width);
}
