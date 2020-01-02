#ifndef SERVERNETWORKCONTROLLER_HPP
#define SERVERNETWORKCONTROLLER_HPP

#include <queue>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "NetworkEvents/Events.hpp"

class ServerNetworkController
{
public:
    ServerNetworkController(int port, Game &game);
    NetworkEvent *getNextEvent();
    bool hasNextEvent();
    void sendEvent(NetworkEvent* event);
    sf::Mutex gameMutex;

private:
    std::list<sf::TcpSocket *> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    void serverLoop();
    sf::Thread serverThread;
    sf::Mutex queueMutex;
    sf::Mutex sendMutex;
    std::queue<NetworkEvent *> events;
    Game &game;
};

#endif