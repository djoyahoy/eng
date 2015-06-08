#ifndef __SPIRIT_H__
#define __SPIRIT_H__

#include "common/orientation.h"
#include "physics/force.h"
#include "physics/mass.h"
#include "gfx/sprite.h"
#include "actor/state_flag.h"

namespace actor
{  
  // TODO : there will be many diff types of spirits. Should have simple base class.
  // TODO : most basic spirit would be mass and sprite.
  struct Spirit
  {
    const int max_hp;
    int hp;
    common::Horizontal horiz = common::Horizontal::RIGHT;
    common::Vertical vert = common::Vertical::NONE;
    StateFlag motion_flag;
    physics::Force force;
    physics::Mass mass;
    gfx::Sprite sprite;
    Spirit(int, const physics::Mass&, const gfx::Sprite&);
  };
}

#endif
