#include "physics/force.h"

#include <cmath>

namespace physics
{
  Force::Force()
  {
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
  }

  int Force::get_dx()
  {
    double int_part;
    x = modf(x, &int_part);
    return static_cast<int>(int_part) + static_cast<int>(vx);
  }

  int Force::get_dy()
  {
    double int_part;
    y = modf(y, &int_part);
    return static_cast<int>(int_part) + static_cast<int>(vy);
  }

  float Force::get_vx() const
  {
    return vx;
  }

  float Force::get_vy() const
  {
    return vy;
  }
  
  void Force::add_x(float dx)
  {
    x += dx;
    vx = 0;
  }

  void Force::add_y(float dy)
  {
    y += dy;
    vy = 0;
  }

  void Force::add_vx(float dx)
  {
    vx += dx;
  }

  void Force::add_vy(float dy)
  {
    vy += dy;
  }

  void Force::set_vx(float dx)
  {
    vx = dx;
  }

  void Force::set_vy(float dy)
  {
    vy = dy;
  }

  void Force::reset()
  {
    x = y = vx = vy = 0;
  }
}
