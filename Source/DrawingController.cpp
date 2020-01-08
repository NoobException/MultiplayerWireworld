
#include "DrawingController.hpp"
#include "graphicSettings.hpp"

#include "Networking/NetworkEvents/NetworkEvent.hpp"

DrawingController::DrawingController(
    Game &game,
    sf::RenderWindow &window,
    ClientNetworkController &networkController) : game(game),
                                                  window(window),
                                                  networkController(networkController)
{
}

void DrawingController::setBegin(int x, int y)
{
    drawnObject.begin = {x, y};
}

void DrawingController::setEnd(int x, int y)
{
    drawnObject.end = {x, y};
}

void DrawingController::setDrawnState(State newState)
{
    drawnState = newState;
}

void DrawingController::setDrawMode(DrawMode newDrawMode)
{
    drawnObject.drawMode = newDrawMode;
}

void DrawingController::nextDrawMode()
{
    int current = (int)drawnObject.drawMode;
    int next = (current + 1) % DrawMode::DRAW_MODE_COUNT;
    drawnObject.drawMode = (DrawMode)next;
}

void DrawingController::onCanvasClick(sf::Event::MouseButtonEvent event)
{
    if (event.button == sf::Mouse::Middle)
        return;

    int x = event.x;
    int y = event.y;

    sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(x, y));
    pos.x /= Settings::CELL_SIZE;
    pos.y /= Settings::CELL_SIZE;

    x = pos.x;
    y = pos.y;
    if (!game.grid_controller->is_on_grid(x, y))
        return;

    State s = drawnState;
    if (event.button == sf::Mouse::Right)
        s = State::EMPTY;
    drawnObject.drawnState = s;

    setBegin(x, y);
    setEnd(x, y);

    if (drawnObject.drawMode == DrawMode::DOTS)
        sendCellChanged(x, y, drawnState);
}

void DrawingController::drawObject(sf::Event::MouseMoveEvent event)
{
    sf::Vector2f pos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y));
    int x, y;
    x = pos.x / Settings::CELL_SIZE;
    y = pos.y / Settings::CELL_SIZE;
    if (!game.grid_controller->is_on_grid(x, y))
        return;

    if (drawnObject.drawMode == DrawMode::DOTS)
        sendCellChanged(x, y, drawnObject.drawnState);
    else
        setEnd(x, y);
}

void DrawingController::onMouseRelease(sf::Event::MouseButtonEvent event)
{
    sendDrawnObject();
}

void DrawingController::sendDrawnObject()
{
    if (drawnObject.drawMode == DrawMode::DOTS)
        return;
    int x0, y0;
    x0 = drawnObject.begin.x;
    y0 = drawnObject.begin.y;

    int x1, y1;
    x1 = drawnObject.end.x;
    y1 = drawnObject.end.y;

    NetworkEvent *event;
    if (drawnObject.drawMode == DrawMode::RECT)
    {
        event = new RectangleChangedEvent(x0, y0, x1, y1, drawnObject.drawnState);
        //game.ghosts.setRectangle(x0, y0, x1, y1, drawnObject.drawnState);
    }
    else if (drawnObject.drawMode == DrawMode::LINE)
    {
        event = new LineChangedEvent(x0, y0, x1, y1, drawnObject.drawnState);
        //game.ghosts.setLine(x0, y0, x1, y1, drawnObject.drawnState);
    }
    setBegin(0, 0);
    setEnd(0, 0);
    networkController.sendEvent(event);
    delete event;
}

void DrawingController::sendCellChanged(int x, int y, State s)
{
    auto current_here = game.grid_controller->get_cell(x, y);
    auto ghost_here = game.ghosts_controller->get_cell(x, y);
    
    //if (s == current_here || s == ghost_here)
      //  return;

    // game.ghosts.setCell(x, y, s);

    NetworkEvent *event = new CellChangedEvent(x, y, s);
    networkController.sendEvent(event);
    delete event;
}

DrawnObject DrawingController::getDrawnObject()
{
    return drawnObject;
}