#include "Network/NetworkEventFactory.hpp"

#include "Network/NetworkEvents/Events.hpp"

using namespace Network;
using namespace sf;

unique_ptr<NetworkEvent> NetworkEventFactory::newNetworkEvent(Packet &data)
{
    unsigned char event_type_byte;
    data >> event_type_byte;
    NetworkEvent::Type event_type = (NetworkEvent::Type)event_type_byte;
    switch (event_type)
    {
    case NetworkEvent::Type::NEW_CLIENT:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new NewPlayerEvent(data)));
        break;
    case NetworkEvent::Type::CELL_CHANGED:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new CellChangedEvent(data)));
        break;
    case NetworkEvent::Type::RECTANGLE_CHANGED:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new RectangleChangedEvent(data)));
        break;
    case NetworkEvent::Type::LINE_CHANGED:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new LineChangedEvent(data)));
        break;
    case NetworkEvent::Type::ADVANCE_SIMULATION:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new AdvanceSimulationEvent(data)));
        break;
    case NetworkEvent::Type::CLEAR_WIRES:
        return unique_ptr<NetworkEvent>(dynamic_cast<NetworkEvent *>(new ClearWiresEvent(data)));
        break;
    default:
        break;
    }
}