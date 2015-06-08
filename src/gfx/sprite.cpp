#include "gfx/sprite.h"

#include "json/json.h"

namespace gfx
{
  Sprite::Sprite(float red, float green, float blue, float width, float height)
  {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->width = width;
    this->height = height;
  }

  void Sprite::set_rgb(float r, float g, float b)
  {
    red = r;
    green = g;
    blue = b;
  }

  void Sprite::set_width(float w)
  {
    width = w;
  }

  Sprite make_sprite(const Json::Value& doc)
  {
    return Sprite(doc["red"].asFloat(),
		  doc["green"].asFloat(),
		  doc["blue"].asFloat(),
		  doc["width"].asFloat(),
		  doc["height"].asFloat());
  }
}
