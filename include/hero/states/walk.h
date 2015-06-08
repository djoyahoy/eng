#ifndef __HERO_WALK_H__
#define __HERO_WALK_H__

#include "hero/state.h"

namespace hero
{
  class Walk : public State
  {
  protected:
    float speed;
  public:
    Walk(float);
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
