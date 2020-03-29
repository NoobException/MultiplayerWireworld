#ifndef UI_WINDOWIMPL_HPP
#define UI_WINDOWIMPL_HPP

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"
#include "Game/Component.hpp"

#include "UI/Window.hpp"
#include "UI/GridRenderer.hpp"
#include "UI/GridController.hpp"

namespace UI
{
class WindowImpl : 
    public Game::Component,
    public Window
{
public:
    WindowImpl(std::shared_ptr<sf::RenderWindow>);
    void set_game(std::shared_ptr<Game::Game>);
    void set_renderer(std::shared_ptr<GridRenderer>);

    void update() override;
    
private:
    std::shared_ptr<Game::Game> game;
    std::shared_ptr<sf::RenderWindow> render_window;
    std::shared_ptr<GridRenderer> grid_renderer;
    std::shared_ptr<GridController> grid_controller;
    void process_events();
};

} // namespace UI
#endif // UI_WINDOW_HPP
