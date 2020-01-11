#ifndef UI_UIPRESENTERIMPL_HPP
#define UI_UIPRESENTERIMPL_HPP

#include "GamePresenter/UIPresenter.hpp"
#include "GamePresenter/GamePresenter.hpp"
#include "UI/Window.hpp"

namespace UI
{
class UIPresenterImpl : public UIPresenter
{
public:
    UIPresenterImpl(UI::Window &);

private:
    UI::Window &window;
};
} // namespace UI

#endif // UI_UIPRESENTERIMPL_HPP