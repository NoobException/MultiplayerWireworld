#ifndef CLIENTNETWORKCONTROLLER_HPP
#define CLIENTNETWORKCONTROLLER_HPP

#include <queue>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "NetworkEvents/Events.hpp"

class ClientNetworkController
{
public:
    ClientNetworkController(sf::IpAddress address, int port);
    NetworkEvent *getNextEvent();
    void sendEvent(NetworkEvent *event);
    bool hasNextEvent();

private:
    sf::TcpSocket socket;
    void clientLoop();
    sf::Thread clientThread;
    sf::Mutex queueMutex;
    std::queue<NetworkEvent *> events;
};
#endif