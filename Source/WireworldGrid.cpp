#include <string>
#include <iostream>

#include "WireworldGrid.hpp"
#include "GridInterface.hpp"
#include "Utils.hpp"

#include "Grid.hpp"

WireworldGrid::WireworldGrid(int width, int height) : grid(nullptr), width(0), height(0)
{
    this->createGrid(width, height);
}

WireworldGrid::WireworldGrid(const WireworldGrid &other) : WireworldGrid(other.width, other.height)
{
    if (this->width != other.width || this->height != other.height)
        throw InvalidGridDimensionsException(width, height);
    for (int i = 0; i < other.width * other.height; i++)
        this->grid[i] = other.grid[i];
}

const WireworldGrid &WireworldGrid::operator=(const WireworldGrid &other)
{
    if (this->width != other.width || this->height != other.height)
        throw InvalidGridDimensionsException(width, height);
    for (int i = 0; i < other.width * other.height; i++)
        this->grid[i] = other.grid[i];
    return other;
}

WireworldGrid::~WireworldGrid()
{
    this->freeGrid();
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
        this->grid[i] = State::EMPTY;
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
            case State::EMPTY:
                new_state = State::EMPTY;
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
void WireworldGrid::setLine(int x1, int y1, int x2, int y2, State state)
{
    std::vector<sf::Vector2i> points = getLine(x1, y1, x2, y2);
    for (sf::Vector2i point : points)
    {
        setCell(point.x, point.y, state);
    }
}
void WireworldGrid::setRectangle(int x1, int y1, int x2, int y2, State state)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            setCell(x, y, state);
}
State WireworldGrid::getCell(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
        throw InvalidGridCoordinatesException(x, y, this->width, this->height);
    return this->grid[y * this->width + x];
}

bool WireworldGrid::isOnGrid(int x, int y)
{
    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
        return false;
    return true;
}

int WireworldGrid::getWidth()
{
    return this->width;
}

int WireworldGrid::getHeight()
{
    return this->height;
}