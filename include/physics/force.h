#ifndef __FORCE_H__
#define __FORCE_H__

namespace physics
{
  class Force
  {
  protected:
    float x;
    float y;
    float vx;
    float vy;
  public:
    Force();
    int get_dx();
    int get_dy();
    float get_vx() const;
    float get_vy() const;
    void add_x(float);
    void add_y(float);
    void add_vx(float);
    void add_vy(float);
    void set_vx(float);
    void set_vy(float);
    void reset();
  };
}

#endif
