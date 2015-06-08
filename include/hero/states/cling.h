#ifndef __HERO_CLING_H__
#define __HERO_CLING_H__

#include "hero/state.h"

namespace hero
{
  class Cling : public State
  {
  protected:
    float speed;
    int ctr;
    common::Horizontal dir;
  public:
    Cling(float);
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
