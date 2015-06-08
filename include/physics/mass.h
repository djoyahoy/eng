#ifndef __MASS_H__
#define __MASS_H__

#include <tuple>
#include <vector>

#include "physics/bound.h"
#include "stage/zone.h"

namespace physics
{
  struct Mass : public Bound
  {
    using Bound::Bound;
    using Bound::overlap;
    bool sweep_x(const stage::Zone&, int&) const;
    bool sweep_y(const stage::Zone&, int&) const;
    bool is_grounded(const stage::Zone&) const;
    bool is_sidled_left(const stage::Zone&) const;
    bool is_sidled_right(const stage::Zone&) const;
    bool is_sidled(const stage::Zone&) const;
    bool overlap_ground(const Mass&) const;

    // for hero
    bool overlap_ladder_up(const stage::Zone&) const;
    bool overlap_ladder_down(const stage::Zone&) const;
    int ladder_pos_up(const stage::Zone&) const;
    int ladder_pos_down(const stage::Zone&) const;
    bool sweep_ladder(const stage::Zone&, int, int&) const;

    // for enemy
    bool sweep_ground(const stage::Zone&, int&) const;
  };
}

#endif
