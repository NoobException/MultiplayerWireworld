#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <SFML/Graphics.hpp>

#include "Game.hpp"

class GameRenderer
{
public:
    GameRenderer(Game &game);
    void run();

private:
    const sf::Vector2i WINDOW_SIZE = {640, 640};
    const sf::Vector2i CANVAS_POS = {0, 0};
    const sf::Vector2i CANVAS_SIZE = {640, 640};
    const sf::Vector2i CANVAS_END = {CANVAS_POS.x + CANVAS_SIZE.x,
                                     CANVAS_POS.y + CANVAS_SIZE.y};
    
    sf::View canvas;
    sf::RenderWindow window;
    Game &game;
    bool running;

    const int CELL_SIZE = 10;
    const float ZOOM_FACTOR = 1.1f;
    float current_zoom = 1;
    void draw();
    void drawCanvas();
    void drawCell(int x, int y);
    void processWindowEvents();

    const sf::Keyboard::Key MOVE_VIEW_KEY = sf::Keyboard::LShift;
    bool movingView();

    sf::Vector2i lastMousePos;
    bool mousePressed;
    bool posInCanvas(int x, int y);
    sf::Vector2i getRelPos(int x, int y);

    void mouseClick(int x, int y, sf::Mouse::Button);
    void mouseRelease(int x, int y);
    void guiClick(int x, int y, sf::Mouse::Button);
    void canvasClick(int x, int y, sf::Mouse::Button);
    void mouseMove(int x, int y);
    void zoom(int x, int y, float z);
};
#endif // GAME_RENDERER_HPP