#ifndef NETWORK_EVENTSOCKET_HPP
#define NETWORK_EVENTSOCKET_HPP

#include <memory>
#include <string>
#include <queue>

#include <SFML/Network.hpp>

#include "Network/NetworkEvents/NetworkEvent.hpp"

using namespace std;
using namespace sf;

namespace Network
{
class EventSocket
{
public:
    EventSocket();
    ~EventSocket();
    void connect(string address, int port);
    void send(NetworkEvent &);
    bool has_next_event();
    unique_ptr<NetworkEvent> get_next_event();

private:
    void thread_loop();
    bool running;
    Mutex queue_mutex;
    queue<unique_ptr<NetworkEvent>> event_queue;
    TcpSocket socket;
    Thread thread;
};
} // namespace Network

#endif //NETWORK_EVENTSOCKET_HPP