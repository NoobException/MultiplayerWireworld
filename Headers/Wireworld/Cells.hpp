#ifndef WIREWORLD_CELLS_HPP
#define WIREWORLD_CELLS_HPP

#include <memory>
#include <vector>

#include "Game/Cells.hpp"
#include "Wireworld/Cell.hpp"

namespace Wireworld
{
class Cells : public Game::Cells
{
public:
    class Iterator;
    
    Cells(std::vector<Cell>&);
    static Cells from_game_cells(std::unique_ptr<Game::Cells>);
    Iterator begin() const;
    Iterator end() const;
private:
    std::vector<Cell>& cells;

};

class Cells::Iterator
{
public:    
    Iterator(const Cells&, int);
    void operator++();
    bool operator!=(const Iterator&);
    Cell operator*();
private:
    const Cells &cells; 
    int current_cell;
    
};
} // namespace Wireworld

#endif // WIREWORLD_CELLS_HPP
