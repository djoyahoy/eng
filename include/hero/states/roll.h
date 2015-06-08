#ifndef __HERO_ROLL_H__
#define __HERO_ROLL_H__

#include <vector>
#include "common/counter.h"
#include "hero/state.h"

namespace hero
{
  class Roll : public State
  {
  protected:
    float speed;
    common::Counter ctr;
    std::vector<float> values;
  public:
    Roll(float, const std::vector<float>&);
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
