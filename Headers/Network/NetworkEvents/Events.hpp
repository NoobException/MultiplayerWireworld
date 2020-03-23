#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <memory>

#include <SFML/Network.hpp>

#include "Game/Game.hpp"
#include "Game/Grid.hpp"
#include "Network/NetworkEvents/NetworkEvent.hpp"

using namespace std;

namespace Network
{
class CellChangedEvent : public NetworkEvent
{
public:
    CellChangedEvent(int x, int y, const Game::CellState &state);
    CellChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;

private:
    int x, y;
    unique_ptr<Game::CellState> state;
};

class NewPlayerEvent : public NetworkEvent
{
public:
    NewPlayerEvent(const Game::Grid &grid);
    NewPlayerEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;

private:
    int width;
    int height;
    unique_ptr<Game::Grid> grid;
};
class AdvanceSimulationEvent : public NetworkEvent
{
public:
    AdvanceSimulationEvent();
    AdvanceSimulationEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;
};
class ClearWiresEvent : public NetworkEvent
{
public:
    ClearWiresEvent();
    ClearWiresEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;
};
class RectangleChangedEvent : public NetworkEvent
{
public:
    RectangleChangedEvent(int x1, int y1, int x2, int y2, const Game::CellState &state);
    RectangleChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;

private:
    int x1, y1, x2, y2;
    unique_ptr<Game::CellState> state;
};
class LineChangedEvent : public NetworkEvent
{
public:
    LineChangedEvent(int x1, int y1, int x2, int y2, const Game::CellState &state);
    LineChangedEvent(sf::Packet &data);
    Type getType() override;
    sf::Packet toPacket() override;
    void apply(Game::Game &) override;

private:
    int x1, y1, x2, y2;
    unique_ptr<Game::CellState> state;
};
} // namespace Network
#endif