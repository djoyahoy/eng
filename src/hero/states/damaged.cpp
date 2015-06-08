#include "hero/states/damaged.h"

// TODO : cannot attack while damaged
namespace hero
{
  Damaged::Damaged(int max) :
    ctr(max)
  {

  }
  
  void Damaged::enter(Spirit& spirit,
			   const stage::Zone& zone,
			   const enemy::EnemyVec& enemies,
			   const prop::PropVec& props)
  {
    ctr.reset();
    spirit.sprite.set_rgb(1.0, 0.2, 0.2);
  }

  void Damaged::exit(Spirit& spirit,
			  const stage::Zone& zone,
			  const enemy::EnemyVec& enemies,
			  const prop::PropVec& props)
  {
    spirit.sprite.set_rgb(1.0, 0.8, 0.2);
  }

  void Damaged::update(Spirit& spirit,
			    const stage::Zone& zone,
			    const enemy::EnemyVec& enemies,
			    const prop::PropVec& props)
  {
    if (ctr.update()) {
      spirit.damage_flag.set(static_cast<int>(DamageState::HEALTHY));
    }
  }
}
