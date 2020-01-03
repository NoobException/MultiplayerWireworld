#ifndef DRAWINGCONTROLLER_HPP
#define DRAWINGCONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Networking/ClientNetworkController.hpp"

enum DrawMode
{
    DOTS,
    LINE,
    RECT,
    DRAW_MODE_COUNT
};

struct DrawnObject
{
    DrawMode drawMode = DrawMode::DOTS;
    State drawnState = State::EMPTY;
    sf::Vector2i begin, end;
};

class DrawingController
{
public:
    DrawingController(Game &game,
                      sf::RenderWindow &window,
                      ClientNetworkController &networkController);

    void setBegin(int x, int y);
    void setEnd(int x, int y);
    void setDrawnState(State newState);
    void setDrawMode(DrawMode newDrawMode);
    void nextDrawMode();

    void onCanvasClick(sf::Event::MouseButtonEvent);
    void drawObject(sf::Event::MouseMoveEvent);

    void onMouseRelease(sf::Event::MouseButtonEvent);
    void sendDrawnObject();
    void sendCellChanged(int x, int y, State state);

    DrawnObject getDrawnObject();

private:
    Game &game;
    State drawnState;
    DrawnObject drawnObject;
    sf::RenderWindow &window;
    ClientNetworkController &networkController;
};

#endif //DRAWINGCONTROLLER_HPP