#ifndef GAMEPRESENTER_GAMEPRESENTERIMPL_HPP
#define GAMEPRESENTER_GAMEPRESENTERIMPL_HPP

#include "Game/GamePresenter.hpp"
#include "GamePresenter/NetworkPresenter.hpp"
#include "GamePresenter/UIPresenter.hpp"

#include "Game/Grid.hpp"

namespace GamePresenter
{
class GamePresenterImpl : public Game::GamePresenter
{
public:
    GamePresenterImpl(NetworkPresenter &network_presenter, UIPresenter &ui_presenter);
    void draw_grid(const Game::Grid &) override;

private:
    NetworkPresenter &network_presenter;
    UIPresenter &ui_presenter;
};
} // namespace GamePresenter

#endif // GAMEPRESENTER_GAMEPRESENTERIMPL_HPP