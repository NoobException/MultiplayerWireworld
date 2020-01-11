#ifndef NETWORK_NETWORKPRESENTERIMPL_HPP
#define NETWORK_NETWORKPRESENTERIMPL_HPP

#include "GameController/NetworkController.hpp"
#include "GameController/GameController.hpp"
#include "Network/Communicator.hpp"

namespace Network
{
class NetworkPresenterImpl : public GameController::NetworkController
{
public:
    NetworkPresenterImpl(Communicator &);

private:
    Communicator &communicator;
}
} // namespace Network

#endif // NETWORK_NETWORKPRESENTERIMPL_HPP
