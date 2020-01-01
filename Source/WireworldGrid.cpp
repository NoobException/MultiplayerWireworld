#include "WireworldGrid.hpp"
#include "GridInterface.hpp"

#include <string>

WireworldGrid::WireworldGrid(int width, int height) : grid(nullptr), width(0), height(0)
{
    this->createGrid(width, height);
}

WireworldGrid::~WireworldGrid()
{
    freeGrid();
}

InvalidGridDimensionsException::InvalidGridDimensionsException(int width, int height) : width(width), height(height)
{
}

const char* InvalidGridDimensionsException::what() const noexcept
{
    const std::string errorMessage = "Cannot create a grid of size " + std::to_string(width) + " x " + std::to_string(height);
    return errorMessage.c_str();
}

InvalidGridCoordinatesException::InvalidGridCoordinatesException(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
{
}

const char* InvalidGridCoordinatesException::what() const noexcept
{
    const std::string errorMessage = "Cordinates (" + std::to_string(x) + ", " + std::to_string(y) + ") are not valid on a grid of size " + std::to_string(width) + " x " + std::to_string(height);
    return errorMessage.c_str();
}

void WireworldGrid::createGrid(int width, int height)
{
    freeGrid();
    if(width <= 0 || height <= 0)
        throw InvalidGridDimensionsException(width, height);
    this->width = width;
    this->height = height;
    this->grid = new State[this->width * this->height];
}

void WireworldGrid::freeGrid()
{
    if(this->grid != nullptr)
        delete this->grid;
    this->grid = nullptr;
    this->width = 0;
    this->height = 0;
}

void WireworldGrid::update()
{
}

void WireworldGrid::setCell(int x, int y, State state)
{
    if(x < 0 || x >= this->width || y < 0 || y >= this->height)
        throw InvalidGridCoordinatesException(x, y, this->width, this->height);
    grid[y * this->height + x] = state;
}

State WireworldGrid::getCell(int x, int y)
{
    if(x < 0 || x >= this->width || y < 0 || y >= this->height)
        throw InvalidGridCoordinatesException(x, y, this->width, this->height);
    return grid[y * this->height + x];
}