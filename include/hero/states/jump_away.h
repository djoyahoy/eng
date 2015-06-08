#ifndef __HERO_JUMP_AWAY_H__
#define __HERO_JUMP_AWAY_H__

#include "common/counter.h"
#include "hero/state.h"

namespace hero
{
  class JumpAway : public State
  {
  protected:
    float speed;
    float jump_speed;
    float dim_speed;
    common::Horizontal dir;
    common::Counter ctr;
  public:
    JumpAway(float, float, float, int);
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
