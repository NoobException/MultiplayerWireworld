#include "Wireworld/Cells.hpp"

using namespace Wireworld;

Cells::Cells(std::vector<Cell>& cells) : cells(cells)
{
}

Cells Cells::from_game_cells(std::unique_ptr<Game::Cells> game_cells)
{
    return *static_cast<Cells*>(game_cells.release());
}

Cells::Iterator Cells::begin() const
{
    return Iterator(*this, 0);
}

Cells::Iterator Cells::end() const
{
    return Iterator(*this, cells.size());
}



Cells::Iterator::Iterator(const Cells& cells, int current_cell) : cells(cells)
{
    this->current_cell = current_cell;
}

void Cells::Iterator::operator++()
{
    ++current_cell;
}


bool Cells::Iterator::operator!=(const Cells::Iterator& other)
{
    return other.current_cell != current_cell;
}

Cell Cells::Iterator::operator*()
{
    return cells.cells[current_cell];
}
