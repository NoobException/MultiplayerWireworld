#include <memory>

#include <SFML/Graphics.hpp>

#include "Game/GameImpl.hpp"
#include "Game/Component.hpp"
#include "UI/WindowImpl.hpp"

#include "Wireworld/Wireworld.hpp"

int main()
{
    std::shared_ptr<sf::RenderWindow> render_window = 
        std::make_shared<sf::RenderWindow>(
            sf::VideoMode(640, 640),
            "Wireworld Test",
            sf::Style::Close | sf::Style::Titlebar);
    
    std::shared_ptr<Wireworld::GridRenderer> grid_renderer =
        std::make_shared<Wireworld::GridRenderer>();
    
    std::shared_ptr<UI::WindowImpl> ui_window =
        std::make_shared<UI::WindowImpl>(render_window);

    Wireworld::Grid grid = Wireworld::Grid{64, 64};

    std::shared_ptr<Game::GameImpl> game =
        std::make_shared<Game::GameImpl>(grid);
    
    ui_window->set_renderer(grid_renderer);
    ui_window->set_game(game);
    game->add_component(ui_window);

    game->start();

    return 0;
}
