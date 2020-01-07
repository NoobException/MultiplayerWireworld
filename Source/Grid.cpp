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

template <typename T>
Grid<T>::Grid(int width, int height)
{
    createGrid(width, height);
}

template <typename T>
void Grid<T>::setCell(int x, int y, T state)
{
    grid[y * width + x] = state;
}

template <typename T>
T Grid<T>::getCell(int x, int y)
{
    return grid[y * width + x];
}

template <typename T>
void Grid<T>::createGrid(int width, int height)
{
    this->width = width;
    this->height = height;
    grid = std::make_unique(new T[width * height]);
}


