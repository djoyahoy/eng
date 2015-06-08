#include <iostream>
#include <fstream>

#include <SDL.h>

#include "common/defines.h"
#include "game/game_sdl2.h"
#include "json/json.h"
#include "gfx/painter_gl21.h"

namespace game
{
  GameSDL2::GameSDL2(std::shared_ptr<input::Controller> controller, std::unique_ptr<hero::Hero> hero,
		     std::unique_ptr<stage::Dungeon> dungeon, std::unique_ptr<gfx::IPainter> painter,
		     gfx::Camera camera) :
    controller(controller),
    hero(std::move(hero)),
    dungeon(std::move(dungeon)),
    painter(std::move(painter)),
    camera(camera)
  {
    frames = 0;    
    cur_time = SDL_GetTicks();
  }

  GameSDL2::~GameSDL2()
  {
    SDL_Quit();
  }

  // TODO : fix up
  void GameSDL2::reload()
  {
    dungeon.reset();

    Json::Value doc;
    Json::Reader reader;
    std::ifstream file("res.json");
    if (!reader.parse(file, doc)) {
      std::cout << reader.getFormattedErrorMessages() << std::endl;
      exit(-1);
    }
    dungeon = stage::make_dungeon(doc);
  }

  // TODO : create separate funcs
  void GameSDL2::step()
  {
    /*******
     * Input
     *******/
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
	running = false;
	break;
      }
    }

    /********
     * Update
     ********/
    unsigned int new_time = SDL_GetTicks();
    frames += new_time - cur_time;
    cur_time = new_time;
    while (frames >= FRAME_TIME) {
      
      // TODO : move into hero func
      // TODO : make a link object
      // set hero link
      hero->spirit.link = nullptr;
      for (auto& p : dungeon->props) {
	if (hero->spirit.mass.overlap_ground(p->spirit.mass)) {
	  hero->spirit.link = &p->spirit;
	  break;
	}
      }

      controller->update();

      for (auto& p : dungeon->props) {
	p->update(*dungeon->zone, hero->spirit);
      }
      hero->update(*dungeon->zone, dungeon->enemies, dungeon->props);
      for (auto& e : dungeon->enemies) {
	e->update(*dungeon->zone, hero->spirit);
      }

      camera.update(*dungeon->zone, *hero);

      frames -= FRAME_TIME;
    }

    float blend = static_cast<float>(frames) / static_cast<float>(FRAME_TIME);

    /*******
     * Paint
     *******/
    // TODO : impl occlusion on enemies, props, and zone
    painter->clear();

    painter->push(camera.bound, blend);
    for (auto& e : dungeon->enemies) {
      e->paint(*painter, blend);
    }
    for (auto& p : dungeon->props) {
      p->paint(*painter, blend);
    }
    dungeon->zone->paint(*painter, blend);
    hero->paint(*painter, blend);
    painter->pop();

    painter->paint_scene();
  }

  std::unique_ptr<GameSDL2> make_game()
  {
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
      std::cerr << "Failed to init SDL. " << SDL_GetError() << std::endl;
      exit(-1);
    }

    // make painter
    std::unique_ptr<gfx::PainterGL21> painter = gfx::make_painter_gl21(640, 360);

    // TODO : make_controller func
    std::shared_ptr<input::Controller> controller = nullptr;
    
    if (SDL_IsGameController(0)) {
      SDL_GameController *hw_controller = SDL_GameControllerOpen(0);
      if (hw_controller) {
	controller = std::make_shared<input::Controller>(hw_controller);
      }
    }

    if (controller == nullptr) {
      std::cerr << "TODO : keyboard controller" << std::endl;
      exit(-1);
    }

    // TODO : make_camera func
    physics::Point c_point;
    gfx::CameraBound c_bound(c_point, ROOM_WIDTH, ROOM_HEIGHT);
    gfx::Camera camera(c_bound);

    // make hero
    std::unique_ptr<hero::Hero> hero = hero::make_hero(32, 64, controller);

    // make dungeon
    Json::Value doc;
    Json::Reader reader;
    std::ifstream file("res.json");
    if (!reader.parse(file, doc)) {
      std::cout << reader.getFormattedErrorMessages() << std::endl;
      exit(-1);
    }
    std::unique_ptr<stage::Dungeon> dungeon = stage::make_dungeon(doc);

    return std::make_unique<GameSDL2>(controller, std::move(hero), std::move(dungeon), std::move(painter), camera);
  }
}
