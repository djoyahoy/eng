#include "hero/states/docile.h"

namespace hero
{
    void Docile::input(Spirit& spirit,
		       const stage::Zone& zone,
		       const enemy::EnemyVec& enemies,
		       const prop::PropVec& props)
  {
    if (spirit.controller->is_pressed(input::Glyph::X)) {
      spirit.action_flag.set(static_cast<int>(ActionState::ATTACK));
    }
  }
}
