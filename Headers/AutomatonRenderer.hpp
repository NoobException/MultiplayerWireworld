#ifndef AUTOMATON_RENDERER_HPP
#define AUTOMATON_RENDERER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
namespace UI
{
class AutomatonRenderer
{
public:
  virtual void render(sf::RenderTarget&) const = 0;
  virtual ~AutomatonRenderer() = default;
};
}  // namespace UI
#endif
