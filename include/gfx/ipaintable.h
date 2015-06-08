#ifndef __IPAINTABLE_H__
#define __IPAINTABLE_H__

#include "gfx/ipainter.h"

namespace gfx
{
  struct IPaintable
  {
    virtual ~IPaintable() {};
    virtual void paint(const IPainter&, float) const = 0;
  };
}

#endif
