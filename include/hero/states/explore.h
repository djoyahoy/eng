#ifndef __HERO_EXPLORE_H__
#define __HERO_EXPLORE_H__

#include "hero/state.h"

namespace hero
{
  class Explore : public State
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
