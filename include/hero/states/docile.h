#ifndef __HERO_DOCILE_H__
#define __HERO_DOCILE_H__

#include "hero/state.h"

namespace hero
{
  class Docile : public State
  {
    void input(Spirit& spirit,
	       const stage::Zone& zone,
	       const enemy::EnemyVec& enemies,
	       const prop::PropVec& props);
  };
}

#endif
