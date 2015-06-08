#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <array>

#include <SDL.h>

namespace input
{
  enum class ButtonState : int
  {
    OFF,
    PRESSED,
    HELD,
    RELEASED,
    TAPPED
  };

  class Button
  {
  private:
    static const int TAP_TIME = 10;
    int ctr = 0;
    ButtonState state = ButtonState::OFF;
  public:
    bool is_on() const;
    bool is_pressed() const;
    void update();
    void press();
    void release();
  };

  enum class Glyph : int
  {
    A,
    B,
    X,
    Y,
    LEFT,
    RIGHT,
    UP,
    DOWN
  };

  class Controller
  {
  private:
    SDL_GameController* hw_controller;
    std::array<Button, 8> buttons = {{Button(), Button(), Button(), Button(), Button(), Button(), Button(), Button()}};
  public:
    Controller(SDL_GameController*);
    ~Controller();
    Controller(const Controller&) = delete;
    bool is_on(const Glyph) const;
    bool is_pressed(const Glyph) const;
    void update();
  };
}

#endif
