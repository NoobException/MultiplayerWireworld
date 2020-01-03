#ifndef CLIENTGAMECONTROLLER_HPP
#define CLIENTGAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>

#include "DrawingController.hpp"
#include "GameRenderer.hpp"
#include "Networking/ClientNetworkController.hpp"


class ClientGameController
{
public:
    ClientGameController(Game &game, ClientNetworkController &controller);
    void run();

private:
    Game &game;
    ClientNetworkController &networkController;
    GameRenderer gameRenderer;
    DrawingController drawingController;

    sf::RenderWindow window;
    bool running;

    int selectedState = 0;

    void processNetworkEvents();
    void processWindowEvents();
    void displayCurrentMode();

    sf::Vector2i lastMousePos;
    bool mousePressed = false;
    void onMouseClick(sf::Event::MouseButtonEvent);
    void onMouseRelease(sf::Event::MouseButtonEvent);
    void onGuiClick(sf::Event::MouseButtonEvent);
    void onCanvasClick(sf::Event::MouseButtonEvent);
    void onMouseMove(sf::Event::MouseMoveEvent);
    void onMouseWheelScroll(sf::Event::MouseWheelScrollEvent);

    bool isPosInCanvas(int x, int y);

    bool movingView();
    void moveView(sf::Event::MouseMoveEvent);
    void drawObject(sf::Event::MouseMoveEvent);

    void sendAdvanceSimulation();
    void sendClearWires();
};

#endif //CLIENT_GAME_CONTROLLER_HPP