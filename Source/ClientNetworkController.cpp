#include "ClientNetworkController.hpp"
#include "NetworkEventFactory.hpp"

ClientNetworkController::ClientNetworkController(sf::IpAddress address, int port) : clientThread(&clientLoop, this)
{
    socket.connect(address, port);
    running = true;
    clientThread.launch();
}

void ClientNetworkController::clientLoop()
{
    while (running)
    {
        sf::Packet data;
        sf::Socket::Status status = socket.receive(data);
        if (status == sf::Socket::Done)
        {
            NetworkEvent *event = NetworkEventFactory::newNetworkEvent(data);
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
void ClientNetworkController::stop()
{
    running = false;
    socket.disconnect();
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