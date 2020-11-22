#ifndef MULTIPLAYER_WIREWORLD_USER_INPUT_HPP
#define MULTIPLAYER_WIREWORLD_USER_INPUT_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "../UserInput.hpp"
#include "Automaton.hpp"
#include "MultiplayerAutomaton.hpp"
#include "MultiplayerWireworld/Shapes.hpp"
#include "Shapes.hpp"

namespace MultiplayerWireworld
{
class UserInput : public UI::UserInput
{
public:
  UserInput(std::shared_ptr<MultiplayerAutomaton>);
  void update(sf::RenderTarget& canvas, sf::Event) override;
  void preview_current_shape(sf::RenderTarget& canvas) const override;
  void set_canvas_position(int x, int y) override;
  bool was_closed() override;
  void draw(UI::TextMenu&) override;

private:
  bool closed = false;
  std::shared_ptr<Game> game;
  struct ScreenCoords
  {
    int x, y;
  };
  Cell::Type current_cell_type = Cell::HEAD;
  std::shared_ptr<MultiplayerAutomaton> automaton;
  Grid::Shape::Type current_shape_type = Grid::Shape::SINGLE_CELL;
  ScreenCoords canvas_position;

  Position last_position;
  Position current_position;
  bool placing_shape = false;
  bool deleting_shape = false;

  void place_shape() const;
  CellShape current_shape() const;
  bool are_coords_valid(ScreenCoords) const;

  void begin_shape(ScreenCoords);
  void end_shape(ScreenCoords);
  void update_shape(ScreenCoords);

  Position screen_to_cell(ScreenCoords) const;
};

}  // namespace MultiplayerWireworld
#endif
