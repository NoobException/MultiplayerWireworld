#include "UI/WindowImpl.hpp"
#include <SFML/Graphics.hpp>

#include "Game/CellCoords.hpp"
#include "Game/CellState.hpp"

using namespace UI;
using namespace sf;

std::unique_ptr<Game::GameEvent> WindowImpl::get_next_game_event()
{
}

bool WindowImpl::has_next_game_event()
{
}

void WindowImpl::draw_grid(const Game::Grid &grid)
{
}
