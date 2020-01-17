#ifndef NETWORK_NETWORKEVENTFACTORY_HPP
#define NETWORK_NETWORKEVENTFACTORY_HPP

#include <SFML/Network.hpp>

#include "Network/NetworkEvents/NetworkEvent.hpp"

namespace Network
{
class NetworkEventFactory
{
public:
  static unique_ptr<NetworkEvent> newNetworkEvent(sf::Packet &data);
};
} // namespace Network

#endif // NETWORK_NETWORKEVENTFACTORY_HPP