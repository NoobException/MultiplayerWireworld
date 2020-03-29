#include "Game/GameImpl.hpp"

using namespace Game;

GameImpl::GameImpl(Grid &grid): grid(grid)
{
    running = false;
}

void GameImpl::update_automaton()
{
}

void GameImpl::set_cells(std::unique_ptr<Cells> cells)
{
    grid.set_cells(move(cells));
}

void GameImpl::update()
{
    for (auto &component : components)
    {
        component->update();
    }
}

bool GameImpl::is_running()
{
    return running;
}

void GameImpl::start()
{
    running = true;
    while (running)
    {
        update();
    }
}

void GameImpl::quit()
{
    running = false;
}

void GameImpl::add_component(std::shared_ptr<Component> component)
{
    components.push_back(component);
}


std::unique_ptr<Cells> GameImpl::changed_cells()
{
   return std::move(grid.get_changed_cells()); 
}

std::unique_ptr<Cells> GameImpl::all_cells()
{
    return std::move(grid.get_all_cells());
}

