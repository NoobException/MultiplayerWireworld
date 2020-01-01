#include "NetworkEventFactory.hpp"

NetworkEvent *NetworkEventFactory::newNetworkEvent(sf::Packet &data)
{
    unsigned char type;
    data >> type;
    switch (type)
    {
    case CELL_CHANGED:
        return new CellChangedEvent(data);
    case NEW_CLIENT:
        return new NewPlayerEvent(data);
    }
};