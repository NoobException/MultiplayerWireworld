#ifndef GAME_GAMELOGICIMPL_HPP
#define GAME_GAMELOGICIMPL_HPP

#include "Game/Automaton.hpp"
#include "Game/GameLogic.hpp"
#include "Game/GamePresenter.hpp"
#include "Game/Grid.hpp"
#include "Game/Shape.hpp"

using namespace std;

namespace Game
{
class GameLogicImpl : public GameLogic
{
public:
    GameLogicImpl(GamePresenter &, Grid &, Automaton &);
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &) override;
    virtual void update_automaton() override;
    virtual void set_custom_shape(const Shape &, const CellState &) override;

private:
    GamePresenter &game_presenter;
    Grid &grid;
    Automaton &automaton;
};
} // namespace Game
#endif // GAME_GAMELOGICIMPL_HPP
