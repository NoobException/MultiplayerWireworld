#ifndef UI_UICONTROLLERIMPL_HPP
#define UI_UICONTROLLERIMPL_HPP

#include <memory>

#include "GameController/ComponentController.hpp"
#include "UI/Window.hpp"

namespace UI
{
class UIControllerImpl : public GameController::ComponentController
{
public:
    UIControllerImpl(UI::Window &);
    virtual std::unique_ptr<GameEvent> get_next_game_event() override;
    virtual bool has_next_game_event() override;

private:
    UI::Window &window;
};
} // namespace UI

#endif // GAMECONTROLLER_UICONTROLLER_HPP