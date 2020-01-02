#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <SFML/System.hpp>
static std::vector<sf::Vector2i> getLine(int x1, int y1, int x2, int y2)
{
    std::vector<sf::Vector2i> ans;
    if (x1 == x2)
    {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++)
            ans.push_back({x1, y});
        return ans;
    }

    double slope = std::abs(static_cast<double>(y2 - y1) / static_cast<double>(x2 - x1));

    if (std::abs(slope) <= 1)
    {
        if (x1 > x2)
        {
            int tmp;
            tmp = x1;
            x1 = x2;
            x2 = tmp;

            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }

        int y = y1;
        double err = 0;
        int dy = (y2 - y1) > 0 ? 1 : (y2 - y1) < 0 ? -1 : 0;
        for (int x = x1; x <= x2; x++)
        {
            ans.push_back({x, y});
            err += slope;
            if (err >= 0.5)
            {
                y += dy;
                err -= 1;
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            int tmp;
            tmp = x1;
            x1 = x2;
            x2 = tmp;

            tmp = y1;
            y1 = y2;
            y2 = tmp;
        }

        int x = x1;
        double err = 0;
        int dx = (x2 - x1) > 0 ? 1 : (x2 - x1) < 0 ? -1 : 0;
        for (int y = y1; y <= y2; y++)
        {
            ans.push_back({x, y});
            err += 1 / slope;
            if (err >= 0.5)
            {
                x += dx;
                err -= 1;
            }
        }
    }
    return ans;
}

#endif