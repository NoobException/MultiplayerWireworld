#ifndef GAMERENDERER_HPP
#define GAMERENDERER_HPP

#include <utility>

#include <SFML/Graphics.hpp>

#include "DrawingController.hpp"
#include "Game.hpp"
#include "Networking/ClientNetworkController.hpp"

class GameRenderer
{
    friend class ClientGameController;

public:
    GameRenderer(Game &game, sf::RenderWindow &window, DrawingController &drawingController);
    void draw();

private:
    sf::View canvas;

    sf::RenderWindow &window;
    Game &game;
    DrawingController &drawingController;

    void drawCanvas();
    void drawBackground();
    void drawGrid();
    void drawGhosts();
    void drawDrawnObject();
    void drawCell(int x, int y, sf::Color color);

    void moveView(int dx, int dy);

    float currentZoom = 1;
    void zoom(sf::Vector2i position, float factor);
};
#endif // GAMERENDERER_HPP
