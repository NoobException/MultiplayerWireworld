#include "Game/Cells.hpp"

using namespace Game;

Cells::Cells(std::vector<std::unique_ptr<Cell>>& cells) : cells(cells)
{
}

Cells::Iterator Cells::begin()
{
    return Iterator(*this, 0);
}

Cells::Iterator Cells::end()
{
    return Iterator(*this, cells.size());
}



Cells::Iterator::Iterator(Cells& cells, int current_cell) : cells(cells)
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

std::unique_ptr<Cell> Cells::Iterator::operator*()
{
    return cells.cells[current_cell]->clone();
}
