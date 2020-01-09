#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <vector>

#include "GridInterface.hpp"


class Grid : GridInterface
{
public:
    Grid(int width, int height);
    ~Grid();

    void set_cell(int x, int y, std::shared_ptr<CellState> state) override;
    std::unique_ptr<CellState> get_cell(int x, int y) override;
    bool is_on_grid(int x, int y) override;

    int get_width() override;
    int get_height() override;

    void update() override {}

private:
    std::vector<std::unique_ptr<CellState>> grid;
    int width, height;
    void create_grid(int width, int height);
};

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

#endif // GRID_HPP