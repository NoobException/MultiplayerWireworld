#ifndef UI_WINDOW_HPP
#define UI_WINDOW_HPP

#include "GamePresenter/UIPresenter.hpp"
#include "GameController/UIController.hpp"

namespace UI
{
class Window : public GamePresenter::UIPresenter
{
    public:
        Window(GameController::UIController &);
    private:
        GameController::UIController &ui_controller;
};
} // UI
#endif // UI_WINDOW_HPP