#ifndef GAME_GAMELOGIC_HPP
#define GAME_GAMELOGIC_HPP

#include "Game/GamePresenter.hpp"
#include "Game/GameController.hpp"
#include "Game/Grid.hpp"
#include "Game/Automaton.hpp"

using namespace std;

namespace Game
{
class GameLogic : GameController
{
public:
    GameLogic(GamePresenter &, Grid &, Automaton &);
    virtual unique_ptr<CellState> get_cell_state(const CellCoords &) override;
    virtual void update_automaton() override;
    virtual void set_custom_shape(const Shape &, const CellState &) override;

private:
    GamePresenter &game_presenter;
    Grid &grid;
    Automaton &automaton;
};
} // namespace Game
#endif // GAME_GAMELOGIC_HPP
