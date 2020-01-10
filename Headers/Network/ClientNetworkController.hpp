#ifndef CLIENTNETWORKCONTROLLER_HPP
#define CLIENTNETWORKCONTROLLER_HPP

#include <queue>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Networking/NetworkEvents/Events.hpp"
#include "Networking/NetworkController.hpp"

class ClientNetworkController : NetworkController
{
public:
    ClientNetworkController(sf::IpAddress address, int port);
    NetworkEvent *getNextEvent();
    virtual void sendEvent(NetworkEvent *event) override;
    virtual bool hasNextEvent() override;
    virtual void stop() override;

private:
    bool running;
    sf::TcpSocket socket;
    virtual void controllerLoop() override;
    sf::Thread clientThread;
    sf::Mutex queueMutex;
    std::queue<NetworkEvent *> events;
};
#endif