#include "physics/bound.h"

#include <algorithm>

namespace physics
{
  Bound::Bound(int width, int height)
  {
    this->width = width;
    this->height = height;
  }

  Bound::Bound(const Point& point, int width, int height) : prev(point), point(point)
  {
    this->width = width;
    this->height = height;
  }

  Point Bound::get_a() const
  {
    return point;
  }

  Point Bound::get_b() const
  {
    return point + Point(0, height);
  }

  Point Bound::get_c() const
  {
    return point + Point(width, height);
  }

  Point Bound::get_d() const
  {
    return point + Point(width, 0);
  }

  Point Bound::get_center() const
  {
    return point + Point(width / 2, height / 2);
  }

  Point Bound::get_prev() const
  {
    return prev;
  }

  int Bound::get_left() const
  {
    return get_a().x;
  }

  int Bound::get_right() const
  {
    return get_d().x;
  }

  int Bound::get_top() const
  {
    return get_b().y;
  }

  int Bound::get_bottom() const
  {
    return get_a().y;
  }

  void Bound::set_a(const Point& a)
  {
    point = a;
  }

  void Bound::set_d(const Point& d)
  {
    point = d - Point(width, 0);
  }

  void Bound::set_center(const Point& center)
  {
    point = center - Point(width / 2, height / 2);
  }

  bool Bound::overlap(const Bound& other) const
  {
    bool overlap_x = true;
    if (get_right() <= other.get_left() ||
	get_left() >= other.get_right()) {
      overlap_x = false;
    } 

    bool overlap_y = true;
    if (get_bottom() >= other.get_top() ||
	get_top() <= other.get_bottom()) {
      overlap_y = false;
    }

    return overlap_x && overlap_y;
  }

  // TODO : use prev to calculate signage of overlap
  static int calc_overlap(int min1, int max1, int min2, int max2)
  {
    int overhaul = std::max(0, std::min(max1, max2) - std::max(min1, min2));
    if (min1 <= min2) {
      overhaul = -overhaul;
    }
    return overhaul;
  }

  int Bound::overlap_x(const Bound& other) const
  {
    return calc_overlap(get_a().x, get_d().x, other.get_a().x, other.get_d().x);
  }

  int Bound::overlap_y(const Bound& other) const
  {
    return calc_overlap(get_a().y, get_b().y, other.get_a().y, other.get_b().y);
  }

  void Bound::update_x(int x)
  {
    prev.x = point.x;
    point.x += x;
  }

  void Bound::update_y(int y)
  {
    prev.y = point.y;
    point.y += y;
  }
}
