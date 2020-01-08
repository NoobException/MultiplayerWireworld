#include "Networking/ServerNetworkController.hpp"
#include "Networking/NetworkEventFactory.hpp"
#include "Game.hpp"
#include <iostream>

ServerNetworkController::ServerNetworkController(int port, Game &game) : serverThread(&controllerLoop, this), game(game)
{
    listener.listen(port);
    selector.add(listener);
    serverThread.launch();
}

void ServerNetworkController::controllerLoop()
{
    while (true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                acceptNewClient();
            }
            else
            {
                processClients();
            }
        }
    }
}

bool ServerNetworkController::hasNextEvent()
{
    return !events.empty();
}

NetworkEvent *ServerNetworkController::getNextEvent()
{
    NetworkEvent *ans = nullptr;
    queueMutex.lock();
    ans = events.front();
    events.pop();
    queueMutex.unlock();
    return ans;
}
void ServerNetworkController::sendEvent(NetworkEvent *event)
{
    sf::Packet packet = event->toPacket();
    sendMutex.lock();
    for (sf::TcpSocket *recepient : clients)
        recepient->send(packet);
    sendMutex.unlock();
}

void ServerNetworkController::acceptNewClient()
{
    sf::TcpSocket *client = new sf::TcpSocket;
    if (listener.accept(*client) == sf::Socket::Done)
    {
        std::cout << "Henlo" << std::endl;
        clients.push_back(client);
        selector.add(*client);
        gameMutex.lock();
        // NewPlayerEvent event(game.grid);
        gameMutex.unlock();
        //sf::Packet packet = event.toPacket();
        //sendPacket(client, packet);
    }
    else
    {
        delete client;
    }
}

void ServerNetworkController::processClients()
{
    for (auto it = clients.begin(); it != clients.end();)
    {
        sf::TcpSocket &client = **it;
        if (!selector.isReady(client))
            continue;

        sf::Packet packet;
        sf::Socket::Status status = client.receive(packet);
        if (status == sf::Socket::Done)
        {
            NetworkEvent *event = NetworkEventFactory::newNetworkEvent(packet);
            queueMutex.lock();
            events.push(event);
            queueMutex.unlock();
            for (sf::TcpSocket *recipient : clients)
                sendPacket(recipient, packet);
            it++;
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cout << "Bye" << std::endl;
            selector.remove(client);
            delete *it;
            it = clients.erase(it);
        }
    }
}

void ServerNetworkController::sendPacket(sf::TcpSocket *client, sf::Packet &packet)
{
    sendMutex.lock();
    client->send(packet);
    sendMutex.unlock();
}