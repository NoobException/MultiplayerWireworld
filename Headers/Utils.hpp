#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <SFML/System.hpp>
static std::vector<sf::Vector2i> getLine(int x1, int y1, int x2, int y2)
{
    std::vector<sf::Vector2i> ans;
    int deltaX = (x2 - x1) > 0 ? 1 : (x2 - x1) < 0 ? -1 : 0;
    int deltaY = (y2 - y1) > 0 ? 1 : (y2 - y1) < 0 ? -1 : 0;
    int x = x1;
    int y = y1;
    int w = abs(x1 - x2) + 1;
    int h = abs(y1 - y2) + 1;
    double ratio = (double)w / h;
    while (x != x2 || y != y2)
    {
        ans.push_back(sf::Vector2i(x, y));
        w = abs(x - x2) + 1;
        h = abs(y - y2) + 1;
        double ratio0, ratio1, ratio2;
        ratio0 = ratio1 = ratio2 = std::numeric_limits<double>::max();
        if (h > 1)
            ratio0 = (double)w / (h - 1);
        if (w > 1)
            ratio1 = (double)(w - 1) / h;
        if (h > 1 && w > 1)
            ratio2 = (double)(w - 1) / (h - 1);
        double minRatio = std::min({ratio0, ratio1, ratio2});
        if (ratio0 == minRatio)
            y += deltaY;
        else if (ratio1 == minRatio)
            x += deltaX;
        else
        {
            x += deltaX;
            y += deltaY;
        }
    }
    ans.push_back(sf::Vector2i(x, y));
    return ans;
}

#endif