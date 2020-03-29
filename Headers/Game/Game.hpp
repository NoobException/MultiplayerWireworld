// Boundary interface for sending and gathering information from the Game
#ifndef GAME_GAMELOGIC_HPP
#define GAME_GAMELOGIC_HPP

#include <memory>

#include "Game/Cells.hpp"

namespace Game
{
class Game
{
public:
    virtual void start() = 0;
    virtual void quit() = 0;
    virtual bool is_running() = 0;
    
    virtual void set_cells(std::unique_ptr<Cells>) = 0;
    virtual void update_automaton() = 0;
    

    virtual std::unique_ptr<Cells> changed_cells() = 0;
    virtual std::unique_ptr<Cells> all_cells() = 0;
};
} // namespace Game

#endif // GAME_GAMELOGIC_HPP
