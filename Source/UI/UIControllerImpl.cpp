#include "UI/UIControllerImpl.hpp"

using namespace UI;

UIControllerImpl::UIControllerImpl(
    GameController::GameController &game_controller,
    UI::Window &window)
    : game_controller(game_controller),
      window(window)
{
}

void UIControllerImpl::start()
{
}