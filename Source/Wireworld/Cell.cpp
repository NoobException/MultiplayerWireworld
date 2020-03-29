#include "Wireworld/Cell.hpp"

using namespace Wireworld;

std::unique_ptr<Game::Cell> Cell::clone()
{
    return std::make_unique<Cell>(*this);
}

Cell Cell::from_unique_ptr(std::unique_ptr<Game::Cell> cell)
{
    return *static_cast<Cell*>(cell.release());
}
