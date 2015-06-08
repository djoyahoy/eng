#include "actor/spirit.h"

namespace actor
{
  Spirit::Spirit(int hp, const physics::Mass& mass, const gfx::Sprite& sprite) : max_hp(hp), hp(hp), mass(mass), sprite(sprite)
  {

  }
}
