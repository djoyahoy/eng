#include "hero/states/common.h"
#include "hero/states/idle.h"

namespace hero
{
  void Idle::input(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    if (check_climb(spirit, zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::CLIMB));
      
    } else if (spirit.controller->is_pressed(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::JUMP));
      
    } else if (spirit.controller->is_pressed(input::Glyph::B)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::ROLL));
      
    } else if (spirit.controller->is_on(input::Glyph::LEFT) ||
	       spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::WALK));
      
    } else if (spirit.controller->is_pressed(input::Glyph::Y)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::EXPLORE));
    }
  }

  void Idle::update(Spirit& spirit,
		    const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    move_x(zone, props, spirit);
    move_y(zone, props, spirit);
    if (!check_ground(zone, props, spirit)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }
}
