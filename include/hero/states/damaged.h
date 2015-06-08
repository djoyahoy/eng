#ifndef __HERO_DAMAGED_H__
#define __HERO_DAMAGED_H__

#include "common/counter.h"
#include "hero/state.h"

namespace hero
{
  class Damaged : public State
  {
  protected:
    common::Counter ctr;
  public:
    Damaged(int);
    void enter(Spirit&,
	       const stage::Zone&,
	       const enemy::EnemyVec&,
	       const prop::PropVec&);
    void exit(Spirit&,
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
