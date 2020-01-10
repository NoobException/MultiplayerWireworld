#include "Game/GameLogicImpl.hpp"
#include "Grid/GridImpl.hpp"
#include "GamePresenter/GamePresenterImpl.hpp"
#include "Automata/Wireworld.hpp"

int main()
{
    Grid::GridImpl grid;
    GamePresenter::GamePresenterImpl presenter;
    Automata::Wireworld automaton;
    Game::GameLogicImpl logic(presenter, grid, automaton);
}