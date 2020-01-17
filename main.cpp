
#include <SFML/Graphics.hpp>

#include "Network/CommunicatorImpl.hpp"
#include "UI/WindowImpl.hpp"
#include "Grid/GridImpl.hpp"
#include "Automata/Wireworld.hpp"

#include "Network/NetworkPresenterImpl.hpp"
#include "GamePresenter/GamePresenterImpl.hpp"

#include "GameController/GameControllerImpl.hpp"
#include "Network/NetworkControllerImpl.hpp"
#include "Game/GameLogicImpl.hpp"

int main()
{
    UI::WindowImpl ui_window(
        sf::VideoMode(640, 640),
        "Wireworld Test",
        sf::Style::Close | sf::Style::Titlebar);

    Network::CommunicatorImpl network_communicator;

    Network::NetworkControllerImpl network_controller(network_communicator);
    Network::NetworkPresenterImpl network_presenter(network_communicator);

    GamePresenter::GamePresenterImpl game_presenter(network_presenter, ui_window);

    Grid::GridImpl grid(64, 64, Automata::WireworldState(Automata::WireworldState::NONE));
    Automata::Wireworld automaton(grid);

    Game::GameLogicImpl logic(game_presenter, grid, automaton);
    GameController::GameControllerImpl game_controller(logic,
                                                       ui_window,
                                                       network_controller);

    game_controller.start();
}
