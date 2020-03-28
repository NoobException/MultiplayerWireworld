#include "Wireworld/Cell.hpp"

using namespace Wireworld;

std::unique_ptr<Game::Cell> Cell::clone()
{
    return std::make_unique<Cell>(*this);
}
