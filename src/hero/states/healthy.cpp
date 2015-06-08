#include "hero/states/healthy.h"

// TODO : fix negative health for hp bar
namespace hero
{
  void Healthy::update(Spirit& spirit,
		       const stage::Zone& zone,
		       const enemy::EnemyVec& enemies,
		       const prop::PropVec& props)
  {
    for (auto& enemy : enemies) {
      if (enemy->is_active() && enemy->spirit.mass.overlap(spirit.mass)) {
	spirit.health--;
	spirit.damage_flag.set(static_cast<int>(DamageState::DAMAGED));
	break;
      }
    }
  }
}
