#include "NetworkEvents/Events.hpp"
#include "Utils.hpp"
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
    game.ghosts.setCell(x, y, State::NONE);
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
        {
            game.grid.setCell(x, y, state);
            game.ghosts.setCell(x, y, State::NONE);
        }
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
    std::vector<sf::Vector2i> points = getLine(x1, y1, x2, y2);
    for (sf::Vector2i point : points)
    {
        game.grid.setCell(point.x, point.y, state);
        game.ghosts.setCell(point.x, point.y, State::NONE);
    }
}

Type LineChangedEvent::getType()
{
    return LINE_CHANGED;
}

sf::Packet LineChangedEvent::toPacket()
{
    sf::Packet packet;
    packet << (unsigned char)LINE_CHANGED;
    packet << this->x1;
    packet << this->y1;
    packet << this->x2;
    packet << this->y2;
    packet << (unsigned char)this->state;
    return packet;
}