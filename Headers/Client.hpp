#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Game.hpp"
#include "Window.hpp"

class Client : public Game
{
public:
  Client(std::shared_ptr<UI::Window> window);
  void start() override;
  void quit() override;
  void update() override;

private:
  bool running;
  std::shared_ptr<UI::Window> window;
};

Client::Client(std::shared_ptr<UI::Window> window)
{
  this->window = window;
  running = false;
}

void Client::start()
{
  running = true;
  while (running) update();
}

void Client::update() { window->update(); }

void Client::quit() { running = false; }

#endif
