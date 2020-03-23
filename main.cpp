#include <memory>

#include <SFML/Graphics.hpp>

#include "Network/CommunicatorImpl.hpp"
#include "UI/WindowImpl.hpp"
#include "Grid/GridImpl.hpp"
#include "Automata/Wireworld.hpp"

#include "Network/NetworkPresenterImpl.hpp"
#include "GamePresenter/GamePresenterImpl.hpp"

#include "Network/NetworkControllerImpl.hpp"
#include "Game/GameImpl.hpp"

int main()
{
    std::shared_ptr<UI::WindowImpl> ui_window =
        std::make_shared<UI::WindowImpl>(
            sf::VideoMode(640, 640),
            "Wireworld Test",
            sf::Style::Close | sf::Style::Titlebar);

    Grid::GridImpl grid(64, 64, Automata::WireworldState(Automata::WireworldState::NONE));
    Automata::Wireworld automaton(grid);
    std::shared_ptr<Game::GameImpl> game =
        std::make_shared<Game::GameImpl>(grid, automaton);

    game->add_controller(ui_window);
    game->add_presenter(ui_window);

    game->start();
}
