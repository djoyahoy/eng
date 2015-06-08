#ifndef __HERO_CLIMB_H__
#define __HERO_CLIMB_H__

#include "hero/state.h"

namespace hero
{
  class Climb : public State
  {
  protected:
    float speed;
  public:
    Climb(float);
    void enter(Spirit&,
	       const stage::Zone&,
	       const enemy::EnemyVec&,
	       const prop::PropVec&);
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
