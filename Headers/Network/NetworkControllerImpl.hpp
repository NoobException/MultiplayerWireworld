#ifndef NETWORK_NETWORKCONTROLLERIMPL_HPP
#define NETWORK_NETWORKCONTROLLERIMPL_HPP

#include "GameController/NetworkController.hpp"
#include "GameController/GameController.hpp"
#include "Network/Communicator.hpp"

namespace Network
{
class NetworkControllerImpl : public GameController::NetworkController
{
public:
    NetworkControllerImpl(
        GameController::GameController &,
        Network::Communicator &);

    virtual void start() override;
    virtual void stop() override;
    virtual void send_event(const GameEvent &) override;

private:
    GameController::GameController &game_controller;
    Network::Communicator &communicator;
};
} // namespace Network

#endif // NETWORK_NETWORKCONTROLLERIMPL_HPP
