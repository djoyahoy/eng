#ifndef __HERO_FALL_H__
#define __HERO_FALL_H__

#include "hero/state.h"

namespace hero
{
  class Fall : public State
  {
  protected:
    float speed;
    float max_gravity;
    float gravity;
  public:
    Fall(float, float, float);
    void exit(Spirit&,
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
