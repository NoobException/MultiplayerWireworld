#ifndef GAME_RENDERER_HPP
#define GAME_RENDERER_HPP

#include <utility>

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Networking/ClientNetworkController.hpp"

enum DrawMode
{DOTS, LINE, RECT};

class GameRenderer
{
public:
    GameRenderer(Game &game, ClientNetworkController &controller);
    void run();

private:
    const sf::Vector2i WINDOW_SIZE = {640, 640};
    const sf::Vector2i CANVAS_POS = {0, 0};
    const sf::Vector2i CANVAS_SIZE = {640, 640};
    const sf::Vector2i CANVAS_END = {CANVAS_POS.x + CANVAS_SIZE.x,
                                     CANVAS_POS.y + CANVAS_SIZE.y};

    const sf::Color EMPTY_COLOR = {20, 20, 20};
    const sf::Color COND_COLOR = {180, 200, 70};
    const sf::Color TAIL_COLOR = {200, 70, 50};
    const sf::Color HEAD_COLOR = {50, 70, 200};

    const sf::Color COLORS[4] = {EMPTY_COLOR,
                                 COND_COLOR,
                                 TAIL_COLOR,
                                 HEAD_COLOR};

    ClientNetworkController &controller;

    sf::View canvas;
    sf::View HUD;

    sf::RenderWindow window;
    Game &game;
    bool running;

    int selected_state = 0;

    const int CELL_SIZE = 10;
    const float ZOOM_FACTOR = 1.1f;
    float current_zoom = 1;

    DrawMode mode = DrawMode::RECT;
    State drawnState;
    std::pair<sf::Vector2i, sf::Vector2i> drawnObject;

    void displayCurrentMode();
    
    void draw();
    void drawCanvas();
    void drawBackground();
    void drawGrid();
    void drawGhosts();
    void drawDrawnObject();
    void drawCell(int x, int y, sf::Color color);

    void processWindowEvents();
    void processNetworkEvents();

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
    void mouseMove(const int x, const int y);
    void zoom(int x, int y, float z);

    void sendDrawnObject();
    void sendCellChanged(int x, int y, State state);

    void advanceSimulation();
};
#endif // GAME_RENDERER_HPP
