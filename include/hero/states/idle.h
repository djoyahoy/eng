#ifndef __HERO_IDLE_H__
#define __HERO_IDLE_H__

#include "hero/state.h"

namespace hero
{
  class Idle : public State
  {
  public:
    void input(Spirit&,
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
