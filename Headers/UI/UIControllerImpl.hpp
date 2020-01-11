#ifndef UI_UICONTROLLERIMPL_HPP
#define UI_UICONTROLLERIMPL_HPP

#include "GameController/UIController.hpp"
#include "GameController/GameController.hpp"
#include "UI/Window.hpp"

namespace UI
{
class UIControllerImpl : public GameController::UIController
{
public:
    UIController(GameController::GameController &,
                 UI::Window &);

private:
    GameController::GameController &game_controller;
    UI::Window &window;
};
} // namespace UI

#endif // GAMECONTROLLER_UICONTROLLER_HPP