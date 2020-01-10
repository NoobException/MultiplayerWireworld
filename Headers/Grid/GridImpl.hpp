#ifndef GRID_GRIDIMPL_HPP
#define GRID_GRIDIMPL_HPP

#include <memory>
#include <vector>

#include "Game/Grid.hpp"
#include "Grid/CellCoordsImpl.hpp"

using namespace std;

namespace Grid
{
class GridImpl : public Game::Grid
{
public:
    GridImpl(int width, int height, const Game::CellState &basic_state);

    virtual void set_cell_state(const Game::CellCoords &, const Game::CellState &) override;
    virtual unique_ptr<Game::CellState> get_cell_state(const Game::CellCoords &) const override;
    virtual bool is_on_grid(const Game::CellCoords &) const override;

    virtual int get_width() const override;
    virtual int get_height() const override;

    virtual unique_ptr<Grid> get_copy() const override;
    virtual void set_grid(const Grid &) override;

    virtual void for_each_field(function<void(const Game::CellCoords &)>) const override;

private:
    vector<unique_ptr<Game::CellState>> grid;
    int width, height;
    void create_grid(int width, int height, const Game::CellState &state);
    void validate_coords(const Game::CellCoords &) const;
    CellCoordsImpl get_coords(const Game::CellCoords &) const;
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