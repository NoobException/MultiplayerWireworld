
#include "graphicSettings.hpp"

const sf::Vector2i Settings::WINDOW_SIZE = {640, 640};
const sf::Vector2i Settings::CANVAS_POS = {0, 0};
const sf::Vector2i Settings::CANVAS_SIZE = {640, 640};
const sf::Vector2i Settings::CANVAS_END = {CANVAS_POS.x + CANVAS_SIZE.x,
                                           CANVAS_POS.y + CANVAS_SIZE.y};
const int Settings::CELL_SIZE = 10;
const float Settings::ZOOM_FACTOR = 1.1f;

const sf::Color Settings::EMPTY_COLOR = {20, 20, 20};
const sf::Color Settings::COND_COLOR = {180, 200, 70};
const sf::Color Settings::TAIL_COLOR = {200, 70, 50};
const sf::Color Settings::HEAD_COLOR = {50, 70, 200};
const sf::Color Settings::COLORS[4] = {Settings::EMPTY_COLOR,
                                       Settings::COND_COLOR,
                                       Settings::TAIL_COLOR,
                                       Settings::HEAD_COLOR};
const std::string Settings::COLOR_NAMES[4] = {"Empty", "Conductor", "Tail", "Head"};

const sf::Keyboard::Key Settings::MOVE_VIEW_KEY = sf::Keyboard::LShift;

const sf::Color Settings::BORDER_COLOR = {255, 255, 255};
const int Settings::BORDER_WIDTH = 8;