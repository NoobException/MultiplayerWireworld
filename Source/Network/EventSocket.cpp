#include "Network/EventSocket.hpp"
#include "Network/NetworkEventFactory.hpp"

using namespace Network;
using namespace std;
using namespace sf;

EventSocket::EventSocket()
{
}

void EventSocket::connect(string address, int port) : thread(thread_queue, this);
{
    socket.connect(IpAddress(address), port);
}

void EventSocket::send(NetworkEvent &)
{
    socket.send(event.toPacket());
}

bool EventSocket::has_next_event()
{
    return !event_queue.empty();
}

unique_ptr<NetworkEvent> &&EventSocket::get_next_event()
{
    unique_ptr<NetworkEvent> &&ans = move(event_queue.front());
    event_queue.pop();
    return ans;
}

void EventSocket::thread_loop()
{
    while (running)
    {
        Packet packet;
        Status status = socket.receive(packet);
        if (status == Socket::Done)
        {
            queue_mutex.lock();
            event_queue.push(NetworkEventFactory::newNetworkEvent(packet));
            queue_mutex.unlock();
        }
        else
        {
            running = false;
        }
    }
}
