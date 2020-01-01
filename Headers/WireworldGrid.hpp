#ifndef WIREWORLDGRID_HPP
#define WIREWORLDGRID_HPP

#include <stdexcept>

#include "GridInterface.hpp"

class InvalidGridDimensionsException : std::exception
{
public:

    InvalidGridDimensionsException(int width, int height);

    const char* what() const noexcept override;

private:

    const int width;
    const int height;
};

class InvalidGridCoordinatesException : std::exception
{
public:

    InvalidGridCoordinatesException(int x, int y, int width, int height);

    const char* what() const noexcept override;

private:

    const int x;
    const int y;
    const int width;
    const int height;
};

class WireworldGrid : GridInterface
{
public:

    WireworldGrid(int width, int height);
    WireworldGrid(const WireworldGrid& other);
    virtual ~WireworldGrid();

    virtual void update() override;

    virtual void setCell(int x, int y, State state) override;
    virtual State getCell(int x, int y);

private:

    State* grid;

    virtual void createGrid(int width, int height);
    virtual void freeGrid();

    int width;
    int height;
};

#endif

