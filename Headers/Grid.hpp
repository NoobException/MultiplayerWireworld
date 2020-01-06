#ifndef GRID_HPP
#define GRID_HPP

#include <memory>

#include "GridInterface.hpp"

class InvalidGridDimensionsException : GridException
{
public:
    InvalidGridDimensionsException(int width, int height);

    const char *what() const noexcept override;

private:
    const int width;
    const int height;
};

class InvalidGridCoordinatesException : GridException
{
public:
    InvalidGridCoordinatesException(int x, int y, int width, int height);

    const char *what() const noexcept override;

private:
    const int x;
    const int y;
    const int width;
    const int height;
};

template <typename T>
class Grid : GridInterface
{
public:
    Grid(int width, int height);
    ~Grid();

    void setCell(int x, int y, T state) override;
    T getCell(int x, int y) override;

    int getWidth() override;
    int getHeight() override;

private:
    std::unique_ptr<T> grid;
    int width, height;
    void createGrid(int width, int height);
};

#endif // GRID_HPP