
#include "Grid.hpp"

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
