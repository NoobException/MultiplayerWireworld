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
            currentByte >>= 2;
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
AdvanceSimulationEvent::AdvanceSimulationEvent(){};
AdvanceSimulationEvent::AdvanceSimulationEvent(sf::Packet &data){};
Type AdvanceSimulationEvent::getType()
{
    return ADVANCE_SIMULATION;
};
sf::Packet AdvanceSimulationEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)ADVANCE_SIMULATION;
    return packet;
};
void AdvanceSimulationEvent::apply(Game &game)
{
    game.grid.update();
};

RectangleChangedEvent::RectangleChangedEvent(int x1, int y1, int x2, int y2, State state)
{
    this->x1 = std::min(x1, x2);
    this->y1 = std::min(y1, y2);
    this->x2 = std::max(x1, x2);
    this->y2 = std::max(y1, y2);

    this->state = state;
}

RectangleChangedEvent::RectangleChangedEvent(sf::Packet &data)
{
    data >> this->x1;
    data >> this->y1;
    data >> this->x2;
    data >> this->y2;
    unsigned char state;
    data >> state;
    this->state = (State)state;
}

void RectangleChangedEvent::apply(Game &game)
{
    for (int x = x1; x <= x2; x++)
        for (int y = y1; y <= y2; y++)
            game.grid.setCell(x, y, state);
}

Type RectangleChangedEvent::getType()
{
    return RECTANGLE_CHANGED;
}

sf::Packet RectangleChangedEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)RECTANGLE_CHANGED;
    packet << this->x1;
    packet << this->y1;
    packet << this->x2;
    packet << this->y2;
    packet << (unsigned char)this->state;
    return packet;
}

LineChangedEvent::LineChangedEvent(int x1, int y1, int x2, int y2, State state)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->state = state;
}

LineChangedEvent::LineChangedEvent(sf::Packet &data)
{
    data >> this->x1;
    data >> this->y1;
    data >> this->x2;
    data >> this->y2;
    unsigned char state;
    data >> state;
    this->state = (State)state;
}

void LineChangedEvent::apply(Game &game)
{
    int deltaX = (x2 - x1) > 0 ? 1 : (x2 - x1) < 0 ? -1 : 0;
    int deltaY = (y2 - y1) > 0 ? 1 : (y2 - y1) < 0 ? -1 : 0;
    int x = x1;
    int y = y1;
    int w = abs(x1 - x2) + 1;
    int h = abs(y1 - y2) + 1;
    double ratio = (double)w / h;
    while (x != x2 || y != y2)
    {
        game.grid.setCell(x, y, state);
        w = abs(x - x2) + 1;
        h = abs(y - y2) + 1;
        double ratio0, ratio1, ratio2;
        ratio0 = ratio1 = ratio2 = std::numeric_limits<double>::max();
        if (h > 1)
            ratio0 = (double)w / (h - 1);
        if (w > 1)
            ratio1 = (double)(w - 1) / h;
        if (h > 1 && w > 1)
            ratio2 = (double)(w - 1) / (h - 1);
        double minRatio = std::min({ratio0, ratio1, ratio2});
        if (ratio0 == minRatio)
            y += deltaY;
        else if (ratio1 == minRatio)
            x += deltaX;
        else
        {
            x += deltaX;
            y += deltaY;
        }
    }
    game.grid.setCell(x, y, state);
}

Type LineChangedEvent::getType()
{
    return LINE_CHANGED;
}

sf::Packet LineChangedEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)RECTANGLE_CHANGED;
    packet << this->x1;
    packet << this->y1;
    packet << this->x2;
    packet << this->y2;
    packet << (unsigned char)this->state;
    return packet;
}