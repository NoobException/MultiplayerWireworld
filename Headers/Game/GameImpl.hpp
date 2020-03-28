// Implementation of Game interface

#ifndef GAME_GAMELOGICIMPL_HPP
#define GAME_GAMELOGICIMPL_HPP

#include <memory>
#include <list>

#include "Game/Game.hpp"
#include "Game/Grid.hpp"
#include "Game/Component.hpp"

namespace Game
{
class GameImpl : public Game
{
public:
    GameImpl(Grid &);
    
    void start() override;
    void quit() override;
    bool is_running() override;
     
    void update_automaton() override;
    
    Cells changed_cells() override;
    Cells all_cells() override;

    void add_component(std::shared_ptr<Component>);

private:
    std::list<std::shared_ptr<Component>> components;
    
    Grid &grid;
    bool running;
    
    void update();
    void process_events();
};
} // namespace Game

#endif // GAME_GAMELOGICIMPL_HPP
