#ifndef SERVERNETWORKCONTROLLER_HPP
#define SERVERNETWORKCONTROLLER_HPP

#include <queue>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Networking/NetworkEvents/Events.hpp"
#include "Networking/NetworkController.hpp"

class ServerNetworkController : NetworkController
{
public:
    ServerNetworkController(int port, Game &game);
    NetworkEvent *getNextEvent() override;
    bool hasNextEvent() override;
    void sendEvent(NetworkEvent *event) override;
    void stop() override{};
    sf::Mutex gameMutex;

private:
    void controllerLoop() override;
    void removeDisconnectedSockets();
    void acceptNewClient();
    void processClients();
    void sendPacket(sf::TcpSocket *client, sf::Packet &packet);

    std::list<sf::TcpSocket *> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    sf::Thread serverThread;
    sf::Mutex queueMutex;
    sf::Mutex sendMutex;
    std::queue<NetworkEvent *> events;
    Game &game;
};

#endif