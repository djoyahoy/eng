#ifndef __ORIENTATION_H__
#define __ORIENTATION_H__

namespace common
{
  enum class Horizontal : int
  {
    NONE,
    LEFT,
    RIGHT
  };

  enum class Vertical : int
  {
    NONE,
    UP,
    DOWN
  };

  struct Orientation
  {
    Horizontal h;
    Vertical v;
  };
}

#endif
