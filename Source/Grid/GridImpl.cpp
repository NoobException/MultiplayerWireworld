#include "Grid/GridImpl.hpp"

using namespace std;
using namespace Grid;

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

GridImpl::GridImpl(int width, int height, const Game::CellState &basic_state)
{
    create_grid(width, height, basic_state);
}

void GridImpl::set_cell_state(const Game::CellCoords &coords, const Game::CellState &state)
{
    validate_coords(coords);
    CellCoordsImpl coords_impl = get_coords(coords);
    grid[coords_impl.y * width + coords_impl.x] = state.copy();
}

unique_ptr<Game::CellState> GridImpl::get_cell_state(const Game::CellCoords &coords) const
{
    validate_coords(coords);
    CellCoordsImpl coords_impl = get_coords(coords);
    return grid[coords_impl.y * width + coords_impl.x]->copy();
}

void GridImpl::create_grid(int width, int height, const Game::CellState &state)
{
    this->width = width;
    this->height = height;
    grid.reserve(width * height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            grid.push_back(state.copy());
        }
    }
}

void GridImpl::validate_coords(const Game::CellCoords &coords) const
{
    CellCoordsImpl coords_impl = get_coords(coords);
    if (!is_on_grid(coords))
        throw InvalidGridCoordinatesException(coords_impl.x, coords_impl.y, width, height);
}

bool GridImpl::is_on_grid(const Game::CellCoords &coords) const
{
    CellCoordsImpl coords_impl = get_coords(coords);
    return coords_impl.x >= 0 && coords_impl.x < width && coords_impl.y >= 0 && coords_impl.y < height;
}

CellCoordsImpl GridImpl::get_coords(const Game::CellCoords &coords) const
{
    return static_cast<const CellCoordsImpl &>(coords);
}

int GridImpl::get_width() const
{
    return width;
}

int GridImpl::get_height() const
{
    return height;
}

unique_ptr<Game::Grid> GridImpl::get_copy() const
{
    unique_ptr<Game::Grid> ans = unique_ptr<Game::Grid>(dynamic_cast<Game::Grid *>(new GridImpl(width, height, *grid[0])));
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            CellCoordsImpl coords(x, y);
            unique_ptr<Game::CellState> state = get_cell_state(coords);
            ans->set_cell_state(coords, *state);
        }
    }
    return ans;
}

void GridImpl::set_grid(const Game::Grid &grid)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            CellCoordsImpl coords(x, y);
            unique_ptr<Game::CellState> state = grid.get_cell_state(coords);
            set_cell_state(coords, *state);
        }
    }
}

void GridImpl::for_each_field(function<void(const Game::CellCoords &)> f) const
{
    for (int x = 0; x <= width; x++)
        for (int y = 0; y <= height; y++)
            f(CellCoordsImpl(x, y));
}