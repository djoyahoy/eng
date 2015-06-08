#ifndef __POINT_H__
#define __POINT_H__

namespace physics
{
  struct Point
  {
    int x;
    int y;
    Point();
    Point(int, int);
    Point operator+(const Point&) const;
    Point operator-(const Point&) const;
    void operator+=(const Point&);
    void operator-=(const Point&);
  };
}

#endif
