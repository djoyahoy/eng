#include "prop/prop.h"

namespace prop
{
  Prop::Prop(const actor::Spirit& spirit, PropStateVec motion) :
    gfx::IPaintable(), motion_states(std::move(motion)), spirit(spirit)
  {
    active = true;
    damaged = false;
    motion_state = 0;
  }

  void Prop::paint(const gfx::IPainter& painter, float blend) const
  {
    if (!active) {
      return;
    }
    painter.paint_sprite(spirit.mass, spirit.sprite, blend);
  }

  void Prop::update(const stage::Zone& zone, hero::Spirit& hero_spirit)
  {
    if (!active) {
      return;
    }
    motion_states[motion_state]->update(spirit, zone, hero_spirit);
    if (spirit.motion_flag.is_set()) {
      motion_states[motion_state]->exit(spirit);
      motion_state = spirit.motion_flag.get();
      motion_states[motion_state]->enter(spirit);
    }
  }
}
