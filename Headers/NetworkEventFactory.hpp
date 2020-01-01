#ifndef NETWORKEVENTFACTORY_HPP
#define NETWORKEVENTFACTORY_HPP
#include <SFML/Network.hpp>
#include "NetworkEvents/Events.hpp"
class NetworkEventFactory
{
public:
  static NetworkEvent *newNetworkEvent(sf::Packet &data);
};
#endif