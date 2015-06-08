#include "hero/states/common.h"
#include "hero/states/jump.h"

// TODO : assuming that dy for jump will always be positive
namespace hero
{
  Jump::Jump(float speed, float jump_speed, int max) :
    speed(speed), jump_speed(jump_speed), ctr(max)
  {

  }
  
  void Jump::enter(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    ctr.reset();
  }

  void Jump::input(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    if (check_climb(spirit, zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::CLIMB));
      
    } else if (!spirit.controller->is_on(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }

  void Jump::update(Spirit& spirit,
		    const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    set_horizontal(spirit, speed);

    move_x(zone, props, spirit);

    spirit.force.set_vy(jump_speed);

    bool collision = move_y(zone, props, spirit);

    if (collision || ctr.update()) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }
}
