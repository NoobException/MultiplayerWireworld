#ifndef GAME_CELLS_HPP
#define GAME_CELLS_HPP

#include <memory>
#include <vector>


#include "Game/Cell.hpp"

namespace Game
{
class Cells
{
public:
    class Iterator;
    
    Cells(std::vector<std::unique_ptr<Cell>>&);
    Iterator begin();
    Iterator end();
private:
    std::vector<std::unique_ptr<Cell>>& cells;
};

class Cells::Iterator
{
public:    
    Iterator(Cells&, int);
    void operator++();
    bool operator!=(const Iterator&);
    std::unique_ptr<Cell> operator*();
private:
    Cells &cells; 
    int current_cell;
    
};

}

#endif // GAME_CELLS_HPP
