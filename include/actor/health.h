#ifndef __HEALTH_H__
#define __HEALTH_H__

namespace actor
{
  class Health
  {
  private:
    int value;
    int max;
  public:
    Health(int);
    void operator--(int);
    void operator++(int);
  };
}

#endif
