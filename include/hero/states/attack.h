#ifndef __HERO_ATTACK_H__
#define __HERO_ATTACK_H__

#include "common/counter.h"
#include "hero/state.h"

namespace hero
{
  class Attack : public State
  {
  protected:
    common::Counter ctr;
  public:
    Attack(int);
    void enter(Spirit&,
	       const stage::Zone&,
	       const enemy::EnemyVec&,
	       const prop::PropVec&);
    void update(Spirit&,
		const stage::Zone&,
		const enemy::EnemyVec&,
		const prop::PropVec&);
  };
}

#endif
