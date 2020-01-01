#include "ServerNetworkController.hpp"
#include "NetworkEventFactory.hpp"
#include "Game.hpp"
#include <iostream>

ServerNetworkController::ServerNetworkController(int port, Game &game) : serverThread(&serverLoop, this), game(game)
{
    listener.listen(port);
    selector.add(listener);
    serverThread.launch();
}

void ServerNetworkController::serverLoop()
{
    while (true)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket *client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    std::cout << "Henlo" << std::endl;
                    clients.push_back(client);
                    selector.add(*client);
                    gameMutex.lock();
                    NewPlayerEvent event(game.grid);
                    gameMutex.unlock();
                    sf::Packet packet = event.toPacket();
                    sendMutex.lock();
                    client->send(packet);
                    sendMutex.unlock();
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                for (std::list<sf::TcpSocket *>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket &client = **it;
                    if (selector.isReady(client))
                    {
                        sf::Packet packet;
                        sf::Socket::Status status = client.receive(packet);
                        if (status == sf::Socket::Done)
                        {
                            NetworkEvent *event = NetworkEventFactory::newNetworkEvent(packet);
                            queueMutex.lock();
                            events.push(event);
                            queueMutex.unlock();
                            sendMutex.lock();
                            for (sf::TcpSocket *recepient : clients)
                                recepient->send(packet);
                            sendMutex.unlock();
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