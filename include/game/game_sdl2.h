#ifndef __GAME_SDL2_H__
#define __GAME_SDL2_H__

#include <memory>

#include "gfx/camera.h"
#include "input/controller.h"
#include "stage/dungeon.h"
#include "hero/hero.h"
#include "game/igame.h"
#include "gfx/ipainter.h"

namespace game
{
  class GameSDL2 : public IGame
  {
  private:
    int frames;
    unsigned int cur_time;
    std::shared_ptr<input::Controller> controller;
    std::unique_ptr<hero::Hero> hero;
    std::unique_ptr<stage::Dungeon> dungeon;
    std::unique_ptr<gfx::IPainter> painter;
    gfx::Camera camera;
  public:
    GameSDL2(std::shared_ptr<input::Controller>, std::unique_ptr<hero::Hero>,
	     std::unique_ptr<stage::Dungeon>, std::unique_ptr<gfx::IPainter>,
	     gfx::Camera);
    ~GameSDL2();
    void reload();
    void step();
  };

  std::unique_ptr<GameSDL2> make_game();
}

#endif
