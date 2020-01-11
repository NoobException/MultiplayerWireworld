#ifndef GAMEPRESENTER_GAMEPRESENTERIMPL_HPP
#define GAMEPRESENTER_GAMEPRESENTERIMPL_HPP

#include "Game/GamePresenter.hpp"
#include "GamePresenter/NetworkPresenter.hpp"
#include "GamePresenter/UIPresenter.hpp"

namespace GamePresenter
{
class GamePresenterImpl : public Game::GamePresenter
{
public:
    GamePresenterImpl(NetworkPresenter &network_presenter, UIPresenter &ui_presenter);

private:
    NetworkPresenter &network_presenter;
    UIPresenter &ui_presenter;
};
} // namespace GamePresenter

#endif // GAMEPRESENTER_GAMEPRESENTERIMPL_HPP