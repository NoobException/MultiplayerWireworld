#ifndef UI_WINDOWIMPL_HPP
#define UI_WINDOWIMPL_HPP

#include <SFML/Graphics.hpp>

#include "Game/GamePresenter.hpp"
#include "Game/GameController.hpp"
#include "Game/Grid.hpp"

#include "Game/GameEvent.hpp"

namespace UI
{
class WindowImpl : public Game::GameController,
                   public Game::GamePresenter,
                   public sf::RenderWindow
{
public:
    template <typename... Args>
    WindowImpl(Args &&... args);
    std::unique_ptr<Game::GameEvent> get_next_game_event() override;
    bool has_next_game_event() override;
    void draw_grid(const Game::Grid &) override;

private:
    sf::View main_view;
};
template <typename... Args>
WindowImpl::WindowImpl(Args &&... args) : RenderWindow(std::forward<Args>(args)...)
{
    setFramerateLimit(60);
}

} // namespace UI
#endif // UI_WINDOW_HPP