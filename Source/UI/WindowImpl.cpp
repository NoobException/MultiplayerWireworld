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
    draw_grid();
}

void WindowImpl::process_events()
{
    sf::Event event;
    while (render_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game->quit();
        }
    }
}


void WindowImpl::draw_grid()
{
    for (auto cell : game->changed_cells())
    {
        grid_renderer->draw_cell(move(cell));
    }
}

