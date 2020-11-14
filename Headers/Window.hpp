#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "AutomatonRenderer.hpp"
#include "Game.hpp"
#include "UserInput.hpp"

namespace UI
{
class Window
{
public:
  Window(
      std::unique_ptr<AutomatonRenderer> automaton_renderer,
      std::unique_ptr<UserInput> user_input);

  void set_game(std::shared_ptr<Game> new_game);
  void update();

private:
  std::shared_ptr<Game> game;
  std::unique_ptr<AutomatonRenderer> automaton_renderer;
  std::unique_ptr<UserInput> user_input;
  sf::RenderWindow window;
  sf::RenderTexture automaton_canvas;
};
}  // namespace UI

#endif
