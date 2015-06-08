#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <vector>

#include "hero/hero.h"
#include "physics/bound.h"
#include "physics/force.h"
#include "stage/zone.h"

// TODO : move camera bound to physics
// TODO : give camera zoom
namespace gfx
{
  struct CameraBound : public physics::Bound
  {
    using Bound::Bound;
    int collide_x(const stage::Zone&, int) const;
    int collide_y(const stage::Zone&, int) const;
  };

  struct Camera
  {
    physics::Force force;
    CameraBound bound;
    Camera(const CameraBound&);
    void update(const stage::Zone&, const hero::Hero&);
  };
}

#endif
