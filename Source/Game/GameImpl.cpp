#include "Game/GameImpl.hpp"

using namespace Game;

GameImpl::GameImpl(
    Grid &grid,
    Automaton &automaton) : grid(grid),
                            automaton(automaton)
{
    running = false;
}

unique_ptr<CellState> GameImpl::get_cell_state(const CellCoords &cell_coords)
{
    return grid.get_cell_state(cell_coords);
}

void GameImpl::update_automaton()
{
    automaton.update();
}

void GameImpl::set_custom_shape(const Shape &shape, const CellState &cell_state)
{
    for (const auto &cell_coords : shape)
    {
        grid.set_cell_state(*cell_coords, cell_state);
    }
}

void GameImpl::update()
{
    for (auto &controller : controllers)
    {
    }

    for (auto &presenter : presenters)
    {
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
        process_events();
        update();
    }
}
void GameImpl::quit()
{
    running = false;
}

void GameImpl::add_controller(std::shared_ptr<GameController> controller)
{
    controllers.push_back(controller);
}

void GameImpl::add_presenter(std::shared_ptr<GamePresenter> presenter)
{
    presenters.push_back(presenter);
}

void GameImpl::process_events()
{
}