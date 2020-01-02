
#include <iostream>

#include "GameRenderer.hpp"
#include "Utils.hpp"

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

GameRenderer::~GameRenderer()
{
}

void GameRenderer::run()
{
    sf::Clock clock;
    while (running && window.isOpen())
    {

        processWindowEvents();
        processNetworkEvents();
        draw();

        std::string colors[4] = {"Empty", "Conductor", "Tail", "Head"};
        std::string modes[3] = {"Dots", "Lines", "Rectangles"};
        std::string color = colors[selected_state];
        std::string m = modes[(int)mode];
        window.setTitle("Wireworld. " + color + " " + m);
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
            case sf::Keyboard::Tab:
                mode = (DrawMode)(((int)mode + 1) % 3);
                break;
            case sf::Keyboard::Space:
                advanceSimulation();
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
    if (!posInCanvas(x, y))
        return;

    sendDrawnObject();
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

    drawnState = (State)selected_state;
    if (b == sf::Mouse::Right)
        drawnState = State::EMPTY;

    drawnObject = {{x, y}, {x, y}};
    sendCellChanged(x, y, drawnState);
}

void GameRenderer::mouseMove(const int x, const int y)
{
    if (!posInCanvas(lastMousePos.x, lastMousePos.y))
        return;

    if (!mousePressed)
        return;

    if (movingView())
    {
        float dx = x - lastMousePos.x;
        float dy = y - lastMousePos.y;
        dx *= current_zoom;
        dy *= current_zoom;
        canvas.move(-dx, -dy);
    }
    else
    {
        sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(x, y));
        int x1, y1;
        x1 = pos.x;
        y1 = pos.y;
        x1 /= CELL_SIZE;
        y1 /= CELL_SIZE;
        if (!game.grid.isOnGrid(x1, y1))
            return;
        if (mode == DrawMode::DOTS)
        {
            State s;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                s = (State)selected_state;
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                s = State::EMPTY;

            sendCellChanged(x1, y1, s);
        }
        else
        {
            int x0 = lastMousePos.x;
            int y0 = lastMousePos.y;
            sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(x0, y0));
            x0 = pos.x;
            y0 = pos.y;
            x0 /= CELL_SIZE;
            y0 /= CELL_SIZE;
            x1 = drawnObject.first.x;
            y1 = drawnObject.first.y;

            drawnObject = {{x1, y1}, {x0, y0}};
        }
    }
    lastMousePos = {x, y};
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
    drawGrid();
    drawGhosts();
    drawDrawnObject();
}

void GameRenderer::drawGrid()
{
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

sf::Color darken(sf::Color color)
{
    int r, g, b;
    r = color.r;
    g = color.g;
    b = color.b;
    return {r / 2, g / 2, b / 2};
}
void GameRenderer::drawGhosts()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            State s = game.ghosts.getCell(x, y);
            if (s == State::NONE)
                continue;
            sf::Color color = darken(COLORS[(int)s]);
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
    bg.setFillColor(EMPTY_COLOR);
    bg.setPosition({0, 0});
    bg.setSize({width * CELL_SIZE, height * CELL_SIZE});
    window.draw(bg);
}

void GameRenderer::drawDrawnObject()
{
    if (mousePressed == false)
        return;

    if (mode == DrawMode::DOTS)
        return;

    int x, y;
    x = drawnObject.first.x;
    y = drawnObject.first.y;
    int x1, y1;
    x1 = drawnObject.second.x;
    y1 = drawnObject.second.y;
    if (mode == DrawMode::RECT)
    {
        sf::RectangleShape rect;

        int x2, y2;
        x2 = std::max(x, x1);
        y2 = std::max(y, y1);
        x1 = std::min(x, x1);
        y1 = std::min(y, y1);

        rect.setPosition({x1 * CELL_SIZE, y1 * CELL_SIZE});
        rect.setSize({(x2 - x1 + 1) * CELL_SIZE - 1, (y2 - y1 + 1) * CELL_SIZE - 1});
        rect.setFillColor({200, 200, 200, 200});
        rect.setOutlineThickness(0);
        window.draw(rect);
    }
    else if (mode == DrawMode::LINE)
    {
        auto points = getLine(x, y, x1, y1);
        for (auto point : points)
        {
            drawCell(point.x, point.y, {200, 200, 200, 200});
        }
    }
}

void GameRenderer::drawCell(int x, int y, sf::Color color)
{
    sf::RectangleShape cell;
    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
    cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
    cell.setOutlineThickness(0);
    cell.setFillColor(color);
    window.draw(cell);
}

void GameRenderer::sendDrawnObject()
{
    if (mode == DrawMode::DOTS)
        return;
    int x0, y0;
    x0 = drawnObject.first.x;
    y0 = drawnObject.first.y;
    int x1, y1;
    x1 = drawnObject.second.x;
    y1 = drawnObject.second.y;

    NetworkEvent *event;
    if (mode == DrawMode::RECT)
    {
        event = new RectangleChangedEvent(x0, y0, x1, y1, drawnState);
        for (int x = x0; x <= x1; x++)
            for (int y = y0; y <= y1; y++)
            {
                game.ghosts.setCell(x, y, drawnState);
            }
    }
    else if (mode == DrawMode::LINE)
    {
        event = new LineChangedEvent(x0, y0, x1, y1, drawnState);
        auto points = getLine(x0, y0, x1, y1);
        for (auto point : points)
        {
            game.ghosts.setCell(point.x, point.y, drawnState);
        }
    }
    drawnObject = {{0, 0}, {0, 0}};
    controller.sendEvent(event);
    delete event;
}

void GameRenderer::sendCellChanged(int x, int y, State s)
{
    State current_here = game.grid.getCell(x, y);
    State ghost_here = game.ghosts.getCell(x, y);
    if (s == current_here || s == ghost_here)
        return;

    game.ghosts.setCell(x, y, s);

    NetworkEvent *event = new CellChangedEvent(x, y, s);
    controller.sendEvent(event);
    delete event;
}

void GameRenderer::advanceSimulation()
{
    NetworkEvent *event = new AdvanceSimulationEvent();
    controller.sendEvent(event);
    delete event;
}