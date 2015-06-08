#include "common/counter.h"

namespace common
{
  Counter::Counter(int interval) : tick(0), interval(interval)
  {

  }

  int Counter::value() const
  {
    return tick;
  }

  void Counter::reset()
  {
    tick = 0;
  }

  bool Counter::update()
  {
    if (++tick >= interval) {
      tick = 0;
      return true;
    }
    return false;
  }
}
