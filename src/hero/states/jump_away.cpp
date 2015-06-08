#include "hero/states/common.h"
#include "hero/states/jump_away.h"

namespace hero
{
  JumpAway::JumpAway(float speed,
		     float jump_speed,
		     float dim_speed,
		     int max) :
    speed(speed),
    jump_speed(jump_speed),
    dim_speed(dim_speed),
    ctr(max)
  {
    dir = common::Horizontal::NONE;
  }
  
  void JumpAway::enter(Spirit& spirit,
		       const stage::Zone& zone,
		       const enemy::EnemyVec& enemies,
		       const prop::PropVec& props)
  {
    ctr.reset();
    dir = spirit.orientation.h;
  }

  void JumpAway::input(Spirit& spirit,
		       const stage::Zone& zone,
		       const enemy::EnemyVec& enemies,
		       const prop::PropVec& props)
  {
    if (check_climb(spirit, zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::CLIMB));
      
    } else if(!spirit.controller->is_on(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }

  void JumpAway::update(Spirit& spirit,
			const stage::Zone& zone,
			const enemy::EnemyVec& enemies,
			const prop::PropVec& props)
  {
    if (dir == common::Horizontal::LEFT) {
      if (spirit.controller->is_on(input::Glyph::LEFT)) {
	spirit.orientation.h = common::Horizontal::LEFT;
	spirit.force.add_x(-speed);
      }
      
    } else if (dir == common::Horizontal::RIGHT) {
      if (spirit.controller->is_on(input::Glyph::RIGHT)) {
	spirit.orientation.h = common::Horizontal::RIGHT;
	spirit.force.add_x(speed);
      }
    }

    move_x(zone, props, spirit);

    if (dir == common::Horizontal::LEFT) {
      if (spirit.controller->is_on(input::Glyph::RIGHT)) {
	spirit.force.set_vy(dim_speed);
	
      } else {
	spirit.force.set_vy(jump_speed);
      }
      
    } else if (dir == common::Horizontal::RIGHT) {
      if (spirit.controller->is_on(input::Glyph::LEFT)) {
	spirit.force.set_vy(dim_speed);
	
      } else {
	spirit.force.set_vy(jump_speed);
      }
    }

    bool collision = move_y(zone, props, spirit);

    if (collision || ctr.update()) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }
}
