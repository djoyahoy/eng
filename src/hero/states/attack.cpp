#include "hero/states/attack.h"

// TODO : attack should end early if horiz dir changes
// TODO : vfx + sfx on attack hit
// TODO : enemy should have damage & invlun states
namespace hero
{
  Attack::Attack(int max) :
    ctr(max)
  {

  }
  
  void Attack::enter(Spirit& spirit,
		     const stage::Zone& zone,
		     const enemy::EnemyVec& enemies,
		     const prop::PropVec& props)
  {
    ctr.reset();
  }

  void Attack::update(Spirit& spirit,
		      const stage::Zone& zone,
		      const enemy::EnemyVec& enemies,
		      const prop::PropVec& props)
  {
    if (ctr.update()) {
      for (auto& enemy : enemies) {
	if (spirit.attack.overlap(enemy->spirit.mass)) {
	  enemy->unhit();
	}
      }

      spirit.action_flag.set(static_cast<int>(ActionState::DOCILE));
      return;
    }

    if (spirit.orientation.h == common::Horizontal::LEFT) {
      spirit.attack.set_d(spirit.mass.get_d());
      
    } else if (spirit.orientation.h == common::Horizontal::RIGHT) {
      spirit.attack.set_a(spirit.mass.get_a());
    }

    for (auto& enemy : enemies) {
      if (spirit.attack.overlap(enemy->spirit.mass)) {
	enemy->hit(1);
      }
    }
  }
}
