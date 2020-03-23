#include "Network/NetworkControllerImpl.hpp"

using namespace std;
using namespace Network;

NetworkControllerImpl::NetworkControllerImpl(
    Network::Communicator &communicator)
    : communicator(communicator)
{
}

unique_ptr<Game::GameEvent> NetworkControllerImpl::get_next_game_event()
{
}
bool NetworkControllerImpl::has_next_game_event()
{
}