#include "Game/GameLogicImpl.hpp"
#include "Grid/GridImpl.hpp"
#include "GamePresenter/GamePresenterImpl.hpp"
#include "Automata/Wireworld.hpp"

int main()
{
    Grid::GridImpl grid(64, 64);
    GamePresenter::GamePresenterImpl presenter;
    Automata::Wireworld automaton(grid);
    Game::GameLogicImpl logic(presenter, grid, automaton);
}