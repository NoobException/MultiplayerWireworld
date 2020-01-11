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
        Communicator &);
}
} // namespace Network

#endif // NETWORK_NETWORKCONTROLLERIMPL_HPP
