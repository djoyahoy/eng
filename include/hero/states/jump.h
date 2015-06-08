#ifndef __HERO_JUMP_H__
#define __HERO_JUMP_H__

#include "common/counter.h"
#include "hero/state.h"

namespace hero
{
  class Jump : public State
  {
  protected:
    float speed;
    float jump_speed;
    common::Counter ctr;
  public:
    Jump(float, float, int);
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
