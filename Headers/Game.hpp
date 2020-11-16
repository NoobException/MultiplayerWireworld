#ifndef GAME_HPP
#define GAME_HPP

class Game
{
public:
  virtual void start() = 0;
  virtual void quit() = 0;
  virtual void update() = 0;
  virtual ~Game() = default;
};

#endif
