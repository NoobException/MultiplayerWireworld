#ifndef GRID_GRIDIMPL_HPP
#define GRID_GRIDIMPL_HPP

#include <memory>
#include <vector>

#include "Game/Grid.hpp"

using namespace std;

namespace Grid
{
class GridImpl : Game::Grid
{
public:
    GridImpl(int width, int height);
    ~GridImpl();

    virtual void set_cell_state(const Game::CellCoords &, const Game::CellState &) override;
    virtual std::unique_ptr<Game::CellState> get_cell_state(const Game::CellCoords &) override;
    virtual bool is_on_grid(const Game::CellCoords &) override;

    virtual int get_width() override;
    virtual int get_height() override;

    virtual unique_ptr<Grid> get_copy();
    virtual void set_grid(const Grid &);

private:
    std::vector<std::unique_ptr<Game::CellState>> grid;
    int width, height;
    void create_grid(int width, int height);
};

class InvalidGridDimensionsException : Game::GridException
{
public:
    InvalidGridDimensionsException(int width, int height);

    const char *what() const noexcept override;

private:
    const int width;
    const int height;
};

class InvalidGridCoordinatesException : Game::GridException
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
} // namespace Grid
#endif // GRID_GRIDIMPL_HPP