#include "Grid.hpp"

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


Grid::Grid(int width, int height)
{
    create_grid(width, height);
}


void Grid::set_cell(int x, int y, std::shared_ptr<CellState> state)
{
    if (!is_on_grid(x, y))
        throw InvalidGridCoordinatesException(x, y, width, height);
    grid[y * width + x] = state;
}


std::unique_ptr<CellState> Grid::get_cell(int x, int y)
{
    if (!is_on_grid(x, y))
        throw InvalidGridCoordinatesException(x, y, width, height);

    return grid[y * width + x];
}


void Grid::create_grid(int width, int height)
{
    this->width = width;
    this->height = height;
    grid = std::make_unique<CellState*> grid(new CellState[width * height]);
}

bool Grid::is_on_grid(int x, int y)
{
    return (x >= 0 && x < width && y >= 0 && y < width);
}


