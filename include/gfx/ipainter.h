#ifndef __IPAINTER_H__
#define __IPAINTER_H__

#include "physics/bound.h"
#include "physics/point.h"
#include "gfx/sprite.h"

namespace gfx
{
  struct IPainter
  {
    virtual ~IPainter() {};
    virtual void clear() const = 0;
    virtual void paint_scene() const = 0;
    virtual void push(float, float) const = 0;
    virtual void push(const physics::Bound&, float) const = 0;
    virtual void pop() const = 0;
    virtual void paint_sprite(float, float, const Sprite&) const = 0;
    virtual void paint_sprite(const physics::Point&, const Sprite&) const = 0;
    virtual void paint_sprite(const physics::Bound&, const Sprite&, float) const = 0;
  };
}
#endif
