#include "physics/point.h"

namespace physics
{
  Point::Point()
  {
    x = y = 0;
  }

  Point::Point(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  Point Point::operator+(const Point& other) const
  {
    return Point(x + other.x, y + other.y);
  }

  Point Point::operator-(const Point& other) const
  {
    return Point(x - other.x, y - other.y);
  }

  void Point::operator+=(const Point& other)
  {
    this->x += other.x;
    this->y += other.y;
  }

  void Point::operator-=(const Point& other)
  {
    this->x -= other.x;
    this->y -= other.y;
  }
}
