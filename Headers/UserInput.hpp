#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "Game.hpp"

namespace UI
{
class UserInput
{
public:
  virtual void update(sf::RenderTarget& canvas, sf::Event) = 0;
  virtual void preview_current_shape(sf::RenderTarget& canvas) const = 0;
  virtual void set_canvas_position(int x, int y) = 0;
};
}  // namespace UI

#endif
