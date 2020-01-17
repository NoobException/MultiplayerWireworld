#include "Network/EventSocket.hpp"
#include "Network/NetworkEventFactory.hpp"

using namespace Network;
using namespace std;
using namespace sf;

EventSocket::EventSocket() : thread(thread_loop, this)
{
}

EventSocket::~EventSocket()
{
    socket.disconnect();
}

void EventSocket::connect(string address, int port)
{
    socket.connect(IpAddress(address), port);
    running = true;
    thread.launch();
}

void EventSocket::send(NetworkEvent &event)
{
    Packet event_packet = event.toPacket();
    socket.send(event_packet);
}

bool EventSocket::has_next_event()
{
    return !event_queue.empty();
}

unique_ptr<NetworkEvent> EventSocket::get_next_event()
{
    queue_mutex.lock();
    unique_ptr<NetworkEvent> ans = move(event_queue.front());
    event_queue.pop();
    queue_mutex.unlock();
    return ans;
}

void EventSocket::thread_loop()
{
    while (running)
    {
        Packet packet;
        Socket::Status status = socket.receive(packet);
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
