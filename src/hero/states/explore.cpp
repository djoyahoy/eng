#include "hero/states/common.h"
#include "hero/states/explore.h"

namespace hero
{
    void Explore::input(Spirit& spirit,
			const stage::Zone& zone,
			const enemy::EnemyVec& enemies,
			const prop::PropVec& props)
  {
    if (spirit.controller->is_on(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
    }
  }

  void Explore::update(Spirit& spirit,
		       const stage::Zone& zone,
		       const enemy::EnemyVec& enemies,
		       const prop::PropVec& props)
  {
    if (spirit.controller->is_on(input::Glyph::LEFT)) {
      spirit.orientation.h = common::Horizontal::LEFT;
      spirit.force.add_x(-8);
      
    } else if (spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.orientation.h = common::Horizontal::RIGHT;
      spirit.force.add_x(8);
    }

    move_x(zone, props, spirit);

    if (spirit.controller->is_on(input::Glyph::UP)) {
      spirit.force.add_y(8);
      
    } else if (spirit.controller->is_on(input::Glyph::DOWN)) {
      spirit.force.add_y(-8);
    }

    move_y(zone, props, spirit);
  }
}
