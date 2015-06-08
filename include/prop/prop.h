#ifndef __PROP_H__
#define __PROP_H__

#include <memory>
#include <vector>

#include "actor/spirit.h"
#include "gfx/ipaintable.h"
#include "gfx/ipainter.h"
#include "prop/prop_state.h"
#include "stage/zone.h"

namespace prop
{
  class Prop : public gfx::IPaintable
  {
  protected:
    bool active;
    bool damaged;
    int motion_state;
    PropStateVec motion_states;
  public:
    actor::Spirit spirit;
    Prop(const actor::Spirit&, PropStateVec);
    void paint(const gfx::IPainter&, float) const;
    void update(const stage::Zone&, hero::Spirit&);
    bool is_active() const { return active; }
  };

  typedef std::vector<std::unique_ptr<Prop>> PropVec;
}

#endif
