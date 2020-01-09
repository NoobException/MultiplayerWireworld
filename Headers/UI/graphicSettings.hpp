/*
    Settings used to display game on screen
*/

#ifndef GRAPHICSETTINGS_HPP
#define GRAPHICSETTINGS_HPP

#include <SFML/Graphics.hpp>

class Settings
{
public:
    static const sf::Vector2i WINDOW_SIZE;
    static const sf::Vector2i CANVAS_POS;
    static const sf::Vector2i CANVAS_SIZE;
    static const sf::Vector2i CANVAS_END;
    static const int CELL_SIZE;
    static const float ZOOM_FACTOR;

    static const sf::Color EMPTY_COLOR;
    static const sf::Color COND_COLOR;
    static const sf::Color TAIL_COLOR;
    static const sf::Color HEAD_COLOR;
    static const sf::Color COLORS[4];
    static const std::string COLOR_NAMES[4];

    static const sf::Keyboard::Key MOVE_VIEW_KEY;

    static const sf::Color BORDER_COLOR;
    static const int BORDER_WIDTH;
};

#endif // GRAPHICSETTINGS_HPP
