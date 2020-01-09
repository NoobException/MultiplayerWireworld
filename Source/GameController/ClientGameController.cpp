
#include "ClientGameController.hpp"
#include "graphicSettings.hpp"

ClientGameController::ClientGameController(
    Game &game,
    ClientNetworkController &networkController) : game(game),
                                                  networkController(networkController),
                                                  gameRenderer(game, window, drawingController),
                                                  drawingController(game, window, networkController),
                                                  window(
                                                      sf::VideoMode(Settings::WINDOW_SIZE.x, Settings::WINDOW_SIZE.y),
                                                      "Wireworld",
                                                      sf::Style::Close | sf::Style::Titlebar),
                                                  running(true)
{
    window.setFramerateLimit(60);
}

void ClientGameController::run()
{
    while (running && window.isOpen())
    {
        processNetworkEvents();
        processWindowEvents();
        displayCurrentMode();
        gameRenderer.draw();
    }
}

void ClientGameController::processNetworkEvents()
{
    while (networkController.hasNextEvent())
    {
        NetworkEvent *event = networkController.getNextEvent();
        event->apply(game);
        delete event;
    }
}

void ClientGameController::processWindowEvents()
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
            onMouseClick(event.mouseButton);
            break;
        case sf::Event::MouseButtonReleased:
            onMouseRelease(event.mouseButton);
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove);
            break;
        case sf::Event::MouseWheelScrolled:
            onMouseWheelScroll(event.mouseWheelScroll);
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Num1:
            case sf::Keyboard::Num2:
            case sf::Keyboard::Num4:
                selectedState = (int)event.key.code - (int)sf::Keyboard::Num1;
                drawingController.setDrawnState((State)selectedState);
                break;
            case sf::Keyboard::Tab:
                drawingController.nextDrawMode();
                break;
            case sf::Keyboard::Space:
                sendAdvanceSimulation();
                break;
            case sf::Keyboard::C:
                sendClearWires();
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

void ClientGameController::onMouseClick(sf::Event::MouseButtonEvent event)
{
    int x = event.x;
    int y = event.y;
    sf::Mouse::Button button = event.button;
    mousePressed = true;
    lastMousePos = {x, y};
    if (movingView())
        return;
    if (!isPosInCanvas(x, y))
        onGuiClick(event);
    else
        drawingController.onCanvasClick(event);
}

void ClientGameController::onMouseRelease(sf::Event::MouseButtonEvent event)
{
    int x = event.x;
    int y = event.y;
    mousePressed = false;
    if (!isPosInCanvas(x, y))
        return;

    drawingController.onMouseRelease(event);
}

void ClientGameController::onGuiClick(sf::Event::MouseButtonEvent event) {}

void ClientGameController::onMouseMove(sf::Event::MouseMoveEvent event)
{
    // Moving mouse has no effect if not pressed
    if (!mousePressed)
        return;

    if (movingView())
    {
        int dx = lastMousePos.x - event.x;
        int dy = lastMousePos.y - event.y;
        gameRenderer.moveView(dx, dy);
    }
    else
    {
        drawingController.drawObject(event);
    }
    lastMousePos = {event.x, event.y};
}

void ClientGameController::onMouseWheelScroll(sf::Event::MouseWheelScrollEvent event)
{
    int x = event.x;
    int y = event.y;
    float delta = event.delta;
    gameRenderer.zoom({x, y}, delta);
}

bool ClientGameController::isPosInCanvas(int x, int y)
{
    if (x >= Settings::CANVAS_POS.x &&
        y >= Settings::CANVAS_POS.y &&
        x < Settings::CANVAS_END.x &&
        y < Settings::CANVAS_END.y)
        return true;
    return false;
}

bool ClientGameController::movingView()
{
    return sf::Keyboard::isKeyPressed(Settings::MOVE_VIEW_KEY);
}

void ClientGameController::displayCurrentMode()
{
    std::string modes[3] = {"Dots", "Lines", "Rectangles"};
    std::string color = Settings::COLOR_NAMES[selectedState];
    std::string m = modes[(int)drawingController.getDrawnObject().drawMode];
    window.setTitle("Wireworld. " + color + " " + m);
}

void ClientGameController::sendAdvanceSimulation()
{
    AdvanceSimulationEvent event;
    networkController.sendEvent(&event);
}

void ClientGameController::sendClearWires()
{
    NetworkEvent *event = new ClearWiresEvent();
    networkController.sendEvent(event);
    delete event;
}