
#include <iostream>

#include "GameRenderer.hpp"
#include "Utils.hpp"

#include "graphicSettings.hpp"

GameRenderer::GameRenderer(
    Game &game,
    sf::RenderWindow &window,
    DrawingController &drawingController) : canvas(sf::FloatRect({0.0, 0.0},
                                                                 (sf::Vector2f)Settings::CANVAS_SIZE)),
                                            window(window),
                                            game(game),
                                            drawingController(drawingController)
{
    canvas.setViewport(sf::FloatRect(Settings::CANVAS_POS.x / Settings::WINDOW_SIZE.x,
                                     Settings::CANVAS_POS.y / Settings::WINDOW_SIZE.y,
                                     Settings::CANVAS_SIZE.x / Settings::WINDOW_SIZE.x,
                                     Settings::CANVAS_SIZE.y / Settings::WINDOW_SIZE.y));
}

void GameRenderer::draw()
{
    window.clear(Settings::EMPTY_COLOR);
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
            CellState s = game.grid_controller->get_cell(x, y);
            sf::Color color = Settings::COLORS[1];
            drawCell(x, y, color);
        }
    }
}

void GameRenderer::drawGhosts()
{
    /*
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 64; y++)
        {
            State s = game.ghosts.getCell(x, y);
            if (s == State::NONE)
                continue;
            sf::Color color = darken(Settings::COLORS[(int)s]);
            drawCell(x, y, color);
        }
    }
    */
}

void GameRenderer::drawBackground()
{
    int width = game.grid_controller->get_width();
    int height = game.grid_controller->get_height();
    sf::RectangleShape bg;
    bg.setOutlineThickness(Settings::BORDER_WIDTH);
    bg.setOutlineColor(Settings::BORDER_COLOR);
    bg.setFillColor(Settings::EMPTY_COLOR);
    bg.setPosition({0, 0});
    bg.setSize({(float)width * Settings::CELL_SIZE, (float)height * Settings::CELL_SIZE});
    window.draw(bg);
}

void GameRenderer::drawDrawnObject()
{
    DrawnObject drawnObject = drawingController.getDrawnObject();
    if (drawnObject.drawMode == DrawMode::DOTS)
        return;

    int x, y;
    x = drawnObject.begin.x;
    y = drawnObject.begin.y;
    int x1, y1;
    x1 = drawnObject.end.x;
    y1 = drawnObject.end.y;
    if (drawnObject.drawMode == DrawMode::RECT)
    {
        sf::RectangleShape rect;

        int x2, y2;
        x2 = std::max(x, x1);
        y2 = std::max(y, y1);
        x1 = std::min(x, x1);
        y1 = std::min(y, y1);

        rect.setPosition((float)x1 * Settings::CELL_SIZE, (float)y1 * Settings::CELL_SIZE);
        rect.setSize(sf::Vector2f((float)(x2 - x1 + 1) * Settings::CELL_SIZE - 1, (float)(y2 - y1 + 1) * Settings::CELL_SIZE - 1));
        rect.setFillColor({200, 200, 200, 200});
        rect.setOutlineThickness(0);
        window.draw(rect);
    }
    else if (drawnObject.drawMode == DrawMode::LINE)
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
    cell.setPosition(x * Settings::CELL_SIZE, y * Settings::CELL_SIZE);
    cell.setSize(sf::Vector2f(Settings::CELL_SIZE - 1, Settings::CELL_SIZE - 1));
    cell.setOutlineThickness(0);
    cell.setFillColor(color);
    window.draw(cell);
}

void GameRenderer::zoom(sf::Vector2i position, float factor)
{
    factor = (factor > 0 ? 1 / Settings::ZOOM_FACTOR : Settings::ZOOM_FACTOR);
    currentZoom *= factor;
    window.setView(canvas);
    const sf::Vector2f before = window.mapPixelToCoords(position);
    canvas.zoom(factor);
    window.setView(canvas);
    const sf::Vector2f after = window.mapPixelToCoords(position);
    canvas.move(before - after);
    window.setView(canvas);
}

void GameRenderer::moveView(int dx, int dy)
{
    canvas.move((float)dx * currentZoom, (float)dy * currentZoom);
}
