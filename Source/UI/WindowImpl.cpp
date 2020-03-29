#include <SFML/Graphics.hpp>

#include "UI/WindowImpl.hpp"

using namespace UI;


WindowImpl::WindowImpl(std::shared_ptr<sf::RenderWindow> render_window)
{
    this->render_window = render_window;
}

void WindowImpl::set_game(std::shared_ptr<Game::Game> game)
{
    this->game = game;
}

void WindowImpl::set_renderer(std::shared_ptr<GridRenderer> renderer)
{
    this->grid_renderer = renderer;
}

void WindowImpl::update()
{
    process_events();
    grid_renderer->draw_cells(*render_window, *game->changed_cells());
    grid_renderer->draw_cells(*render_window, *game->all_cells());
    render_window->display();
}


#include "Wireworld/Cells.hpp"
void set_cell(std::shared_ptr<Game::Game> game, int x, int y)
{
    std::vector<Wireworld::Cell> cells;
    Wireworld::Cell cell;
    cell.coords.x = x / 10;
    cell.coords.y = y / 10;
    cell.state.type = Wireworld::Cell::State::Head;
    cells.push_back(cell);
    std::unique_ptr<Game::Cells> ptr = std::make_unique<Wireworld::Cells>(cells);
    game->set_cells(move(ptr));
}

void WindowImpl::process_events()
{
    sf::Event event;
    while (render_window->pollEvent(event)) 
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            game->quit();
            break;
        case sf::Event::MouseButtonPressed:
            set_cell(game, event.mouseButton.x, event.mouseButton.y);
            break;
        }

    }
}


