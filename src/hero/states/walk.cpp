#include "hero/states/common.h"
#include "hero/states/walk.h"

// TODO : still need to handle XY movers (stickiness on Y part of motion).
namespace hero
{
  Walk::Walk(float speed) :
    speed(speed)
  {

  }
  
  void Walk::input(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    if (check_climb(spirit, zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::CLIMB));
      
    } else if(spirit.controller->is_pressed(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::JUMP));
      
    } else if (spirit.controller->is_pressed(input::Glyph::B)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::ROLL));
      
    } else if (!spirit.controller->is_on(input::Glyph::LEFT) &&
	       !spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
    }
  }

  void Walk::update(Spirit& spirit,
		    const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    set_horizontal(spirit, speed);

    move_x(zone, props, spirit);

    move_y(zone, props, spirit);

    if (!check_ground(zone, props, spirit)) {
      if (spirit.link != nullptr) {
	// Prevent stickiness when attached to a prop.
	spirit.mass.update_y(-1);
      }
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }
}
