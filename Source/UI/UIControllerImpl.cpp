#include "UI/UIControllerImpl.hpp"

using namespace std;
using namespace UI;

UIControllerImpl::UIControllerImpl(
    UI::Window &window)
    : window(window)
{
}
unique_ptr<GameEvent> UIControllerImpl::get_next_game_event()
{
}
bool UIControllerImpl::has_next_game_event()
{
}