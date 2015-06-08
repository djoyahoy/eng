#ifndef __BOUND_H__
#define __BOUND_H__

#include "physics/point.h"

/**
Bound winding:

   B------>C
   ^       |
   |       |
   |       v
   A<------D

 **/
namespace physics
{
  class Bound
  {
  protected:
    Point prev;
    Point point;
    int width;
    int height;
  public:
    Bound(int, int);
    Bound(const Point&, int, int);
    Point get_a() const;
    Point get_b() const;
    Point get_c() const;
    Point get_d() const;
    Point get_center() const;
    Point get_prev() const;
    int get_left() const;
    int get_right() const;
    int get_top() const;
    int get_bottom() const;
    void set_a(const Point&);
    void set_d(const Point&);
    void set_center(const Point&);
    bool overlap(const Bound&) const;
    int overlap_x(const Bound&) const;
    int overlap_y(const Bound&) const;
    void update_x(int);
    void update_y(int);
  };
}

#endif
