#ifndef __IGAME_H__
#define __IGAME_H__

namespace game
{
  struct IGame
  {
    virtual ~IGame() {};
    bool running = true;
    virtual void reload() {};
    virtual void step() = 0;
  };
}

#endif
