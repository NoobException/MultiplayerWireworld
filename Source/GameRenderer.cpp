
#include <iostream>

#include "GameRenderer.hpp"

GameRenderer::GameRenderer(Game &game, ClientNetworkController &controller) : canvas(sf::FloatRect({0.0, 0.0},
                                                                                                   (sf::Vector2f)CANVAS_SIZE)),
                                                                              window(
                                                                                  sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                                                                                  "Wireworld Client",
                                                                                  sf::Style::Close | sf::Style::Titlebar),
                                                                              game(game),
                                                                              running(true),
                                                                              controller(controller)
{
    canvas.setViewport(sf::FloatRect(CANVAS_POS.x / WINDOW_SIZE.x,
                                     CANVAS_POS.y / WINDOW_SIZE.y,
                                     CANVAS_SIZE.x / WINDOW_SIZE.x,
                                     CANVAS_SIZE.y / WINDOW_SIZE.y));
    window.setFramerateLimit(60);
}

void GameRenderer::run()
{
    sf::Clock clock;
    while (running && window.isOpen())
    {
        /*
        if (clock.getElapsedTime().asMilliseconds() >= 100)
        {
            game.grid.update();
            clock.restart();
        }*/

        processWindowEvents();
        processNetworkEvents();
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
            case sf::Keyboard::Num4:
                selected_state = (int)event.key.code - (int)sf::Keyboard::Num1;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void GameRenderer::processNetworkEvents()
{
    while (controller.hasNextEvent())
    {
        NetworkEvent *event = controller.getNextEvent();
        event->apply(game);
        delete event;
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
    return {static_cast<int>(pos.x), static_cast<int>(pos.y)};
}

void GameRenderer::mouseClick(int x, int y, sf::Mouse::Button b)
{
    mousePressed = true;
    lastMousePos = {x, y};
    if (movingView())
        return;
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
    if (!game.grid.isOnGrid(x, y))
        return;

    State s = (State)selected_state;
    if (b == sf::Mouse::Right)
        s = State::NONE;

    // game.grid.setCell(x, y, s);
    sendCellChanged(x, y, s);
}

void GameRenderer::mouseMove(int x, int y)
{
    if (!posInCanvas(lastMousePos.x, lastMousePos.y))
        return;

    if (movingView() && mousePressed)
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
    drawBackground();
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

void GameRenderer::drawBackground()
{
    int width = game.grid.getWidth();
    int height = game.grid.getHeight();
    sf::RectangleShape bg;
    bg.setOutlineThickness(4);
    bg.setOutlineColor({255, 255, 255});
    bg.setFillColor(NONE_COLOR);
    bg.setPosition({0, 0});
    bg.setSize({width * CELL_SIZE, height * CELL_SIZE});
    window.draw(bg);
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

void GameRenderer::sendCellChanged(int x, int y, State s)
{
    NetworkEvent *event = new CellChangedEvent(x, y, s);
    controller.sendEvent(event);
    delete event;
}