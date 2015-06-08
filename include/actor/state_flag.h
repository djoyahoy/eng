#ifndef __STATE_FLAG_H__
#define __STATE_FLAG_H__

namespace actor
{
  class StateFlag
  {
  private:
    int state;
  public:
    StateFlag();
    int get();
    void set(int);
    bool is_set() const;
  };
}

#endif
