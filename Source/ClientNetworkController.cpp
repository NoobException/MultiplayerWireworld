#include "ClientNetworkController.hpp"

ClientNetworkController::ClientNetworkController(sf::IpAddress address, int port) : clientThread(&clientLoop, this)
{
    socket.connect(address, port);
    clientThread.launch();
}

void ClientNetworkController::clientLoop()
{
    while (true)
    {
        sf::Packet data;
        if (socket.receive(data) == sf::Socket::Done)
        {
            NetworkEvent *event = nullptr;
            queueMutex.lock();
            events.push(event);
            queueMutex.unlock();
        }
    }
}

void ClientNetworkController::sendEvent(NetworkEvent *event)
{
    sf::Packet packet = event->toPacket();
    socket.send(packet);
}

bool ClientNetworkController::hasNextEvent()
{
    return !events.empty();
}

NetworkEvent *ClientNetworkController::getNextEvent()
{
    NetworkEvent *ans = nullptr;
    queueMutex.lock();
    ans = events.front();
    events.pop();
    queueMutex.unlock();
    return ans;
}