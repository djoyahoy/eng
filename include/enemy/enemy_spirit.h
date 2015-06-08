#ifndef __ENEMY_SPIRIT_H__
#define __ENEMY_SPIRIT_H__

#include "actor/spirit.h"

namespace enemy
{
  struct EnemySpirit : public actor::Spirit
  {
    unsigned int dmg;
    EnemySpirit(int, unsigned int, const physics::Mass&, const gfx::Sprite&);
  };
}

#endif
