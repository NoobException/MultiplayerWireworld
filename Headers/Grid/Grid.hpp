#ifndef GRID_GRID_HPP
#define GRID_GRID_HPP

struct Position
{
  int x, y;
  bool operator==(const Position& rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  bool operator<(const Position& rhs) const
  {
    if (x == rhs.x) return y < rhs.y;
    return x < rhs.x;
  }
};

#endif
