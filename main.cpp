#include <memory>

#include "Client.hpp"
#include "MultiplayerWireworld/Automaton.hpp"
#include "MultiplayerWireworld/MultiplayerAutomaton.hpp"
#include "MultiplayerWireworld/Renderer.hpp"
#include "MultiplayerWireworld/UserInput.hpp"
#include "Window.hpp"

int main()
{
  auto multiplayer_wireworld =
      std::make_shared<MultiplayerWireworld::MultiplayerAutomaton>();
  auto wireworld_renderer =
      std::make_unique<MultiplayerWireworld::Renderer>(multiplayer_wireworld);
  auto wireworld_input =
      std::make_unique<MultiplayerWireworld::UserInput>(multiplayer_wireworld);

  auto window = std::make_shared<UI::Window>(
      std::move(wireworld_renderer), std::move(wireworld_input));
  auto client = std::make_shared<Client>(window);

  window->set_game(client);
  client->start();
}
