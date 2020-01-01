
#include <iostream>

#include "GameRenderer.hpp"

GameRenderer::GameRenderer(Game &game) : game(game),
                                         window(
                                             sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                                             "Wireworld Client",
                                             sf::Style::Close | sf::Style::Titlebar),
                                         canvas(sf::FloatRect({0.0, 0.0},
                                                              (sf::Vector2f)CANVAS_SIZE)),
                                         running(true)
{
    canvas.setViewport(sf::FloatRect(CANVAS_POS.x / WINDOW_SIZE.x,
                                     CANVAS_POS.y / WINDOW_SIZE.y,
                                     CANVAS_SIZE.x / WINDOW_SIZE.x,
                                     CANVAS_SIZE.y / WINDOW_SIZE.y));
}

void GameRenderer::run()
{
    sf::Clock clock;
    while (running && window.isOpen())
    {
        if (clock.getElapsedTime().asMilliseconds() >= 100)
        {
            game.grid.update();
            clock.restart();
        }

        processWindowEvents();
        draw();
    }
}

void GameRenderer::processWindowEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            running = false;
            break;
        case sf::Event::MouseButtonPressed:
            mouseClick(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            mouseRelease(event.mouseButton.x, event.mouseButton.y);
            break;
        case sf::Event::MouseMoved:
            mouseMove(event.mouseMove.x, event.mouseMove.y);
            break;
        case sf::Event::MouseWheelScrolled:
            zoom(event.mouseWheelScroll.x,
                 event.mouseWheelScroll.y,
                 event.mouseWheelScroll.delta);
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Num1:
                case sf::Keyboard::Num2:
                case sf::Keyboard::Num3:
                case sf::Keyboard::Num4:
                    selected_state = (int)event.key.code - (int)sf::Keyboard::Num1;
                    break;
            }
        }
    }
}

bool GameRenderer::movingView()
{
    return sf::Keyboard::isKeyPressed(MOVE_VIEW_KEY);
}

bool GameRenderer::posInCanvas(int x, int y)
{
    if (x >= CANVAS_POS.x &&
        y >= CANVAS_POS.y &&
        x < CANVAS_END.x &&
        y < CANVAS_END.y)
        return true;
    return false;
}

sf::Vector2i GameRenderer::getRelPos(int x, int y)
{
    window.setView(canvas);
    sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(x, y));
    return {pos.x, pos.y};
}

void GameRenderer::mouseClick(int x, int y, sf::Mouse::Button b)
{
    lastMousePos = {x, y};
    if (movingView())
        return;
    mousePressed = true;
    if (!posInCanvas(x, y))
        guiClick(x, y, b);
    else
        canvasClick(x, y, b);
}

void GameRenderer::mouseRelease(int x, int y)
{
    mousePressed = false;
}

void GameRenderer::guiClick(int x, int y, sf::Mouse::Button b) {}
void GameRenderer::canvasClick(int x, int y, sf::Mouse::Button b) 
{
    sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(x, y));
    pos.x /= CELL_SIZE;
    pos.y /= CELL_SIZE;
    x = pos.x;
    y = pos.y;
    // State s = (b == sf::Mouse::Left ? State::COND : State::NONE);
    State s = (State)selected_state;
    game.grid.setCell(pos.x, pos.y, s);
}


void GameRenderer::mouseMove(int x, int y)
{
    if (!posInCanvas(lastMousePos.x, lastMousePos.y))
        return;

    if (movingView() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        float dx = x - lastMousePos.x;
        float dy = y - lastMousePos.y;
        dx *= current_zoom;
        dy *= current_zoom;
        canvas.move(-dx, -dy);
        lastMousePos = {x, y};
    }
}

void GameRenderer::zoom(int x, int y, float z)
{
    z = (z > 0 ? 1 / ZOOM_FACTOR : ZOOM_FACTOR);
    current_zoom *= z;
    window.setView(canvas);
    const sf::Vector2f before = window.mapPixelToCoords(sf::Vector2i(x, y));
    canvas.zoom(z);
    window.setView(canvas);
    const sf::Vector2f after = window.mapPixelToCoords(sf::Vector2i(x, y));
    canvas.move(before - after);
    window.setView(canvas);
}

void GameRenderer::draw()
{
    window.clear({20, 20, 20});
    drawCanvas();
    window.display();
}

void GameRenderer::drawCanvas()
{
    window.setView(canvas);
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            State s = game.grid.getCell(x, y);
            sf::Color color = COLORS[(int)s];
            drawCell(x, y, color);
        }
    }
}

void GameRenderer::drawCell(int x, int y, sf::Color color)
{
    sf::RectangleShape cell;
    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
    cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    cell.setOutlineThickness(0);
    cell.setOutlineColor(sf::Color(40, 40, 40));
    cell.setFillColor(color);
    window.draw(cell);
}