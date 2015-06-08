#include "actor/state_flag.h"

namespace actor
{
  StateFlag::StateFlag()
  {
    state = -1;
  }

  int StateFlag::get()
  {
    int tmp = state;
    state = -1;
    return tmp;
  }

  void StateFlag::set(int s)
  {
    state = s;
  }

  bool StateFlag::is_set() const
  {
    return state != -1;
  }
}
