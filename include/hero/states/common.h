#ifndef __HERO_COMMON_H__
#define __HERO_COMMON_H__

#include "hero/state.h"

namespace hero
{
  bool move_x(const stage::Zone&, const prop::PropVec&, Spirit&);

  bool move_y(const stage::Zone&, const prop::PropVec&, Spirit&);

  // TODO : could change overlap bound based on direction of spirit
  bool check_climb(Spirit&, const stage::Zone&);

  bool check_ground(const stage::Zone&, const prop::PropVec&, Spirit&);

  void set_horizontal(Spirit&, const float);

  void shift_hero(Spirit&, const int);
}

#endif
