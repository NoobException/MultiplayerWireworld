#include "WireworldGrid.hpp"
#include "GridInterface.hpp"

#include <string>

WireworldGrid::WireworldGrid(int width, int height) : grid(nullptr), width(0), height(0)
{
    this->createGrid(width, height);
}

WireworldGrid::WireworldGrid(const WireworldGrid &other) : WireworldGrid(other.width, other.height)
{
    for (int i = 0; i < other.width * other.height; i++)
        this->grid[i] = other.grid[i];
}

WireworldGrid::~WireworldGrid()
{
    this->freeGrid();
}

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

void WireworldGrid::createGrid(int width, int height)
{
    freeGrid();
    if (width <= 0 || height <= 0)
        throw InvalidGridDimensionsException(width, height);
    this->width = width;
    this->height = height;
    this->grid = new State[this->width * this->height];
    for (int i = 0; i < this->width * this->height; i++)
        this->grid[i] = State::NONE;
}

void WireworldGrid::freeGrid()
{
    if (this->grid != nullptr)
        delete this->grid;
    this->grid = nullptr;
    this->width = 0;
    this->height = 0;
}

void WireworldGrid::update()
{
    State *new_grid = new State[this->width * this->height];
    for (int x = 0; x < this->width; x++)
        for (int y = 0; y < this->height; y++)
        {
            int index = y * this->width + x;
            State current_state = grid[index];
            State new_state;
            switch (current_state)
            {
            case State::NONE:
                new_state = State::NONE;
                break;
            case State::HEAD:
                new_state = State::TAIL;
                break;
            case State::TAIL:
                new_state = State::COND;
                break;
            case State::COND:
                int n = 0;
                for (int dx = -1; dx < 2; dx++)
                    for (int dy = -1; dy < 2; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                            continue;

                        if (getCell(nx, ny) == State::HEAD)
                            n++;
                    }
                new_state = (n == 1 || n == 2 ? State::HEAD : State::COND);
                break;
            }
            new_grid[index] = new_state;
        }

    delete[] grid;
    grid = new_grid;
}

void WireworldGrid::setCell(int x, int y, State state)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
        throw InvalidGridCoordinatesException(x, y, this->width, this->height);
    this->grid[y * this->width + x] = state;
}

State WireworldGrid::getCell(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
        throw InvalidGridCoordinatesException(x, y, this->width, this->height);
    return this->grid[y * this->width + x];
}

int WireworldGrid::getWidth()
{
    return this->width;
}

int WireworldGrid::getHeight()
{
    return this->height;
}