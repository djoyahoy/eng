#ifndef __COUNTER_H__
#define __COUNTER_H__

namespace common
{
  class Counter
  {
  private:
    int tick;
    int interval;
  public:
    Counter(int);
    int value() const;
    void reset();
    bool update();
  };
}

#endif
