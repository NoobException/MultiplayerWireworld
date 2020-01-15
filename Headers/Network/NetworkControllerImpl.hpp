#ifndef NETWORK_NETWORKCONTROLLERIMPL_HPP
#define NETWORK_NETWORKCONTROLLERIMPL_HPP

#include <memory>

#include "GameController/ComponentController.hpp"
#include "GameController/GameEvent.hpp"
#include "Network/Communicator.hpp"

namespace Network
{
class NetworkControllerImpl : public GameController::ComponentController
{
public:
    NetworkControllerImpl(Network::Communicator &);
    virtual std::unique_ptr<GameEvent> get_next_game_event() override;
    virtual bool has_next_game_event() override;

private:
    Network::Communicator &communicator;
};
} // namespace Network

#endif // NETWORK_NETWORKCONTROLLERIMPL_HPP
