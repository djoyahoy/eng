#include <algorithm>
#include "actor/health.h"

namespace actor
{
  Health::Health(int max) :
    max(max)
  {

  }

  void Health::operator--(int)
  {
    value = std::max<int>(0, value - 1);
  }

  void Health::operator++(int)
  {
    value = std::min<int>(max, value + 1);
  }
}
