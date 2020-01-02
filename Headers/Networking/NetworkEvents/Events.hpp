#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Network.hpp>
#include "WireworldGrid.hpp"
#include "Networking/NetworkEvents/NetworkEvent.hpp"

class CellChangedEvent : public NetworkEvent
{
public:
    CellChangedEvent(int x, int y, State state);
    CellChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game &game) override;

private:
    int x, y;
    State state;
};

class NewPlayerEvent : public NetworkEvent
{
public:
    NewPlayerEvent(WireworldGrid grid);
    NewPlayerEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game &game) override;

private:
    int width;
    int height;
    WireworldGrid grid;
};
class AdvanceSimulationEvent : public NetworkEvent
{
public:
    AdvanceSimulationEvent();
    AdvanceSimulationEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game &game) override;
};
class RectangleChangedEvent : public NetworkEvent
{
public:
    RectangleChangedEvent(int x1, int y1, int x2, int y2, State state);
    RectangleChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game &game) override;

private:
    int x1, y1, x2, y2;
    State state;
};
class LineChangedEvent : public NetworkEvent
{
public:
    LineChangedEvent(int x1, int y1, int x2, int y2, State state);
    LineChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game &game) override;

private:
    int x1, y1, x2, y2;
    State state;
};

#endif