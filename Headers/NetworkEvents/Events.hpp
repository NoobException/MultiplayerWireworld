#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Network.hpp>
#include "WireworldGrid.hpp"
#include "NetworkEvents/NetworkEvent.hpp"

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
#endif