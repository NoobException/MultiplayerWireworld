// Implementation of Game interface

#ifndef GAME_GAMELOGICIMPL_HPP
#define GAME_GAMELOGICIMPL_HPP

#include <memory>
#include <list>

#include "Game/Automaton.hpp"
#include "Game/Game.hpp"
#include "Game/GamePresenter.hpp"
#include "Game/GameController.hpp"
#include "Game/Grid.hpp"
#include "Game/Shape.hpp"

namespace Game
{
class GameImpl : public Game
{
public:
    GameImpl(Grid &, Automaton &);
    virtual std::unique_ptr<CellState> get_cell_state(const CellCoords &) override;
    virtual void set_custom_shape(const Shape &, const CellState &) override;
    void update() override;
    void update_automaton() override;
    bool is_running() override;
    void start() override;
    void quit() override;

    void add_controller(std::shared_ptr<GameController>);
    void add_presenter(std::shared_ptr<GamePresenter>);

private:
    std::list<std::shared_ptr<GameController>> controllers;
    std::list<std::shared_ptr<GamePresenter>> presenters;
    void process_events();

    Grid &grid;
    Automaton &automaton;
    bool running;
};
} // namespace Game

#endif // GAME_GAMELOGICIMPL_HPP
