#include "Networking/NetworkEventFactory.hpp"

NetworkEvent *NetworkEventFactory::newNetworkEvent(sf::Packet &data)
{
    unsigned char type;
    data >> type;
    switch (type)
    {

    case NEW_CLIENT:
        return new NewPlayerEvent(data);
    case CELL_CHANGED:
        return new CellChangedEvent(data);
    case RECTANGLE_CHANGED:
        return new RectangleChangedEvent(data);
    case LINE_CHANGED:
        return new LineChangedEvent(data);
    case ADVANCE_SIMULATION:
        return new AdvanceSimulationEvent(data);
    }
};