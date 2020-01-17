#ifndef UI_WINDOWIMPL_HPP
#define UI_WINDOWIMPL_HPP

#include <SFML/Graphics.hpp>

#include "GameController/ComponentController.hpp"
#include "GamePresenter/UIPresenter.hpp"

namespace UI
{
class WindowImpl : public GameController::ComponentController,
                   public GamePresenter::UIPresenter,
                   public sf::RenderWindow
{
public:
    template <typename... Args>
    WindowImpl(Args &&... args);
    std::unique_ptr<GameEvent> get_next_game_event() override;
    bool has_next_game_event() override;

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