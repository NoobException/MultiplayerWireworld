#include "GamePresenter/GamePresenterImpl.hpp"

using namespace GamePresenter;

GamePresenterImpl::GamePresenterImpl(
    NetworkPresenter &network_presenter,
    UIPresenter &ui_presenter)
    : network_presenter(network_presenter),
      ui_presenter(ui_presenter)
{
}

void GamePresenterImpl::draw_grid(const Game::Grid &grid)
{
    ui_presenter.draw_grid(grid);
}