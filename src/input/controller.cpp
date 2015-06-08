#include "input/controller.h"

namespace input
{
  /*********
   * Button
   *********/
  bool Button::is_on() const
  {
    if (state == ButtonState::PRESSED ||
	state == ButtonState::HELD ||
	state == ButtonState::TAPPED) {
      return true;
    }
    return false;
  }

  bool Button::is_pressed() const
  {
    return state == ButtonState::PRESSED;
  }

  void Button::update()
  {
    if (state != ButtonState::RELEASED) {
      ctr = 0;
    }

    switch(state) {
    case ButtonState::PRESSED:
      state = ButtonState::HELD;
      break;
    case ButtonState::TAPPED:
      state = ButtonState::HELD;
      break;
    case ButtonState::RELEASED:
      if (++ctr >= TAP_TIME) {
	state = ButtonState::OFF;
      }
      break;
    default:
      break;
    }
  }

  void Button::press()
  {
    switch(state) {
    case ButtonState::OFF:
      state = ButtonState::PRESSED;
      break;
    case ButtonState::RELEASED:
      state = ButtonState::TAPPED;
      break;
    default:
      break;
    }
  }

  void Button::release()
  {
    switch(state) {
    case ButtonState::PRESSED:
      state = ButtonState::RELEASED;
      break;
    case ButtonState::HELD:
      state = ButtonState::OFF;
      break;
    case ButtonState::TAPPED:
      state = ButtonState::OFF;
      break;
    default:
      break;
    }
  }

  /*************
   * Controller
   *************/
  static const std::array<std::pair<Glyph, SDL_GameControllerButton>, 8> BUTTON_MAP = {
    {
      {Glyph::A, SDL_CONTROLLER_BUTTON_A},
      {Glyph::B, SDL_CONTROLLER_BUTTON_B},
      {Glyph::X, SDL_CONTROLLER_BUTTON_X},
      {Glyph::Y, SDL_CONTROLLER_BUTTON_Y},
      {Glyph::LEFT, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
      {Glyph::RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
      {Glyph::UP, SDL_CONTROLLER_BUTTON_DPAD_UP},
      {Glyph::DOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN},
    }
  };

  Controller::Controller(SDL_GameController* hw_controller)
  {
    this->hw_controller = hw_controller;
  }

  Controller::~Controller()
  {
    // TODO : close correctly
    //SDL_GameControllerClose(hw_controller);
  }

  bool Controller::is_on(const Glyph name) const
  {
    return buttons[static_cast<int>(name)].is_on();
  }

  bool Controller::is_pressed(const Glyph name) const
  {
    return buttons[static_cast<int>(name)].is_pressed();
  }

  // TODO : handle axis
  void Controller::update()
  {
    for (const auto m : BUTTON_MAP) {
      buttons[static_cast<int>(m.first)].update();
      if (SDL_GameControllerGetButton(hw_controller, m.second)) {
	buttons[static_cast<int>(m.first)].press();
      } else {
	buttons[static_cast<int>(m.first)].release();
      } 
    }
  }
}
