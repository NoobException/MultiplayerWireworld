#ifndef WIREWORLD_GRID_HPP
#define WIREWORLD_GRID_HPP

#include <memory>
#include <vector>
#include <exception>

#include "Game/Grid.hpp"
#include "Wireworld/Cell.hpp"
#include "Game/Cells.hpp"

namespace Wireworld
{
class Grid : public Game::Grid
{
public:
    Grid(int width, int height);

    virtual bool is_on_grid(Game::Cell::Coords&) const override;
    virtual void set_cell_state(Game::Cell::Coords&, Game::Cell::State&) override;
    virtual const Game::Cell::State& get_cell_state(Game::Cell::Coords&) const override;

    virtual void set_cells(std::unique_ptr<Game::Cells>) override;
    
    virtual int get_width() const override;
    virtual int get_height() const override;

    virtual std::unique_ptr<Game::Cells> get_changed_cells() override;
    virtual std::unique_ptr<Game::Cells> get_all_cells() override;

private:
    std::vector<Cell> all_cells;
    std::vector<Cell> changed_cells;
    int width, height;
    
    Cell::Coords extract_coords(Game::Cell::Coords&);
    Cell::State extract_state(Game::Cell::State&);

    void create_grid();
};

class InvalidGridDimensions: std::exception
{
public:
    InvalidGridDimensions(int width, int height);

    const char *what() const noexcept override;

private:
    const int width;
    const int height;
};

class CoordsNotOnGrid : std::exception
{
public:
    CoordsNotOnGrid(Cell::Coords);
    const char *what() const noexcept override;

private:
    Cell::Coords coords;
};

} // namespace Wireworld
#endif // WIREWORLD_GRID_HPP
