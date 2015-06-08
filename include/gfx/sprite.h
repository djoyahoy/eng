#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <memory>
#include <vector>

#include "json/json-forwards.h"

namespace gfx
{
  class Sprite
  {
  private:
    float red;
    float green;
    float blue;
    float width;
    float height;
  public:
    Sprite(float, float, float, float, float);
    inline float get_red() const { return red; }
    inline float get_green() const { return green; }
    inline float get_blue() const { return blue; }
    inline float get_width() const { return width; }
    inline float get_height() const { return height; }
    void set_rgb(float, float, float);
    void set_width(float);
  };

  Sprite make_sprite(const Json::Value&);

  typedef std::vector<Sprite> SpriteVec;
}

#endif
