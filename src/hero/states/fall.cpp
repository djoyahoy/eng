#include "hero/states/common.h"
#include "hero/states/fall.h"

// TODO : assuming that dy for fall will always be negative
// TODO : do not add to velocities
// TODO : carrying state between updates with force is silly and confusing
namespace hero
{
  Fall::Fall(float speed, float max, float gravity) :
    speed(speed), max_gravity(max), gravity(gravity)
  {

  }
  
  void Fall::exit(Spirit& spirit,
		  const stage::Zone& zone,
		  const enemy::EnemyVec& enemies,
		  const prop::PropVec& props)
  {
    spirit.force.reset(); 
  }

  void Fall::input(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    if (check_climb(spirit, zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::CLIMB));
    }
  }

  void Fall::update(Spirit& spirit,
		    const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    set_horizontal(spirit, speed);

    bool collision = move_x(zone, props, spirit);

    if (spirit.force.get_vy() > max_gravity) {
      spirit.force.add_vy(gravity);
    } else {
      spirit.force.set_vy(max_gravity);
    }

    move_y(zone, props, spirit);

    if (check_ground(zone, props, spirit)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
      
    } else if (collision) {
      // TODO : remove this check and force set if you just want
      //        to hit jump to do triangle jumps
      if (spirit.controller->is_on(input::Glyph::LEFT) ||
	  spirit.controller->is_on(input::Glyph::RIGHT)) {
	spirit.motion_flag.set(static_cast<int>(MotionState::CLING));
	
      } else {
	spirit.force.add_x(0);
      }
    }
  }
}
