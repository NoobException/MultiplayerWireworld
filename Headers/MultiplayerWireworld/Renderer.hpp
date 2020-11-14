#ifndef MULTIPLAYER_WIREWORLD_RENDERER_HPP
#define MULTIPLAYER_WIREWORLD_RENDERER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "Automaton.hpp"
#include "AutomatonRenderer.hpp"
#include "MultiplayerAutomaton.hpp"

namespace MultiplayerWireworld
{
class Renderer : public UI::AutomatonRenderer
{
public:
  Renderer(std::shared_ptr<MultiplayerAutomaton>);
  void render(sf::RenderTarget&) const override;

private:
  std::shared_ptr<MultiplayerAutomaton> automaton;
  void render_cell(sf::RenderTarget&, MultiplayerCell) const;
};
}  // namespace MultiplayerWireworld
#endif
