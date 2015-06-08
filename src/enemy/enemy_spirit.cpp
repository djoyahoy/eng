#include "enemy/enemy_spirit.h"

namespace enemy
{
  EnemySpirit::EnemySpirit(int hp,
			   unsigned int dmg,
			   const physics::Mass& mass,
			   const gfx::Sprite& sprite) :
    Spirit(hp, mass, sprite)
  {
    this->dmg = dmg;
  }
}
