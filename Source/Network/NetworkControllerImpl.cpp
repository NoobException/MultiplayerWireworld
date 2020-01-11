#include "Network/NetworkControllerImpl.hpp"

using namespace Network;

NetworkControllerImpl::NetworkControllerImpl(
    GameController::GameController &game_controller,
    Network::Communicator &communicator)
    : game_controller(game_controller),
      communicator(communicator)
{
}

void NetworkControllerImpl::start() {}
void NetworkControllerImpl::stop() {}
void NetworkControllerImpl::send_event(const GameEvent &game_event) {}