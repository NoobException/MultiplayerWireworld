#include "Game/GameLogicImpl.hpp"
#include "Grid/GridImpl.hpp"
#include "GamePresenter/GamePresenterImpl.hpp"
#include "GameController/GameControllerImpl.hpp"
#include "Automata/Wireworld.hpp"
#include "Network/Communicator.hpp"
#include "UI/Window.hpp"

int main()
{
    Grid::GridImpl grid(64, 64);
    Automata::Wireworld automaton(grid);

    Network::NetworkPresenterImpl network_presenter;
    UI::UIPresenterImpl ui_presenter;

    GamePresenter::GamePresenterImpl presenter(network_presenter, ui_presenter);
    Game::GameLogicImpl logic(presenter, grid, automaton);
    GameController::GameControllerImpl game_controller(logic);

    Network::NetworkControllerImpl network_controller(game_controller);
    UI::UIControllerImpl ui_controller(game_controller);

    UI::Window ui_window(ui_controller, ui_presenter);
    Network::Communicator network_communicator(network_controller, network_presenter);

    logic.start();
}
