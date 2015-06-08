#ifndef __HERO_HEALTHY_H__
#define __HERO_HEALTHY_H__

#include "hero/state.h"

namespace hero
{
  class Healthy : public State
  {
  public:
    void update(Spirit&,
		const stage::Zone&,
		const enemy::EnemyVec&,
		const prop::PropVec&);
  };
}

#endif
