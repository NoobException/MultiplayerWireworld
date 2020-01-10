#ifndef NETWORK_NETWORKEVENTFACTORY_HPP
#define NETWORK_NETWORKEVENTFACTORY_HPP

#include <SFML/Network.hpp>
#include "NetworkEvents/Events.hpp"

namespace Network
{
class NetworkEventFactory
{
public:
  static NetworkEvent *newNetworkEvent(sf::Packet &data);
};
} // Network

#endif // NETWORK_NETWORKEVENTFACTORY_HPP