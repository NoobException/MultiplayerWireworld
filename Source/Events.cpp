#include "NetworkEvents/Events.hpp"

CellChangedEvent::CellChangedEvent(int x, int y, State state)
{
    this->x = x;
    this->y = y;
    this->state = state;
}

CellChangedEvent::CellChangedEvent(sf::Packet &data)
{
    data >> this->x;
    data >> this->y;
    unsigned char state;
    data >> state;
    this->state = (State)state;
}

void CellChangedEvent::apply(Game &game)
{
    game.grid.setCell(x, y, state);
}

Type CellChangedEvent::getType()
{
    return CELL_CHANGED;
}

sf::Packet CellChangedEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)CELL_CHANGED;
    packet << this->x;
    packet << this->y;
    packet << (unsigned char)this->state;
    return packet;
}

NewPlayerEvent::NewPlayerEvent(WireworldGrid grid) : grid(grid)
{
    this->width = grid.getWidth();
    this->height = grid.getHeight();
}
void NewPlayerEvent::apply(Game &game)
{
    game.grid = grid;
}

int getIntFromPacket(sf::Packet &data)
{
    int a;
    data >> a;
    return a;
}
NewPlayerEvent::NewPlayerEvent(sf::Packet &data) : width(getIntFromPacket(data)), height(getIntFromPacket(data)), grid(width, height)
{
    unsigned char currentByte;
    data >> currentByte;
    int currentPosition = 0;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            unsigned char state = currentByte & (unsigned char)3;
            state >>= 2;
            currentPosition++;
            if (currentPosition == 4)
            {
                currentPosition = 0;
                data >> currentByte;
            }
            grid.setCell(x, y, (State)state);
        }
    }
}

Type NewPlayerEvent::getType()
{
    return NEW_CLIENT;
}

sf::Packet NewPlayerEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)NEW_CLIENT;
    packet << width;
    packet << height;
    int currentPosition = 0;
    unsigned char currentByte = 0;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            unsigned char state = (unsigned char)grid.getCell(x, y);
            state <<= currentPosition * 2;
            currentByte |= state;
            currentPosition++;
            if (currentPosition == 4)
            {
                packet << currentByte;
                currentByte = 0;
                currentPosition = 0;
            }
        }
    }
    if (currentPosition != 0)
        packet << currentByte;
    return packet;
}