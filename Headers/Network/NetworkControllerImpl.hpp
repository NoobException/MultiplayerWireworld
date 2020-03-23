#ifndef NETWORK_NETWORKCONTROLLERIMPL_HPP
#define NETWORK_NETWORKCONTROLLERIMPL_HPP

#include <memory>

#include "Game/GameController.hpp"
#include "Game/GameEvent.hpp"
#include "Network/Communicator.hpp"

namespace Network
{
class NetworkControllerImpl : public Game::GameController
{
public:
    NetworkControllerImpl(Network::Communicator &);
    virtual std::unique_ptr<Game::GameEvent> get_next_game_event() override;
    virtual bool has_next_game_event() override;

private:
    Network::Communicator &communicator;
};
} // namespace Network

#endif // NETWORK_NETWORKCONTROLLERIMPL_HPP
