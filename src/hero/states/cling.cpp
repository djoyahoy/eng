#include "hero/states/cling.h"
#include "hero/states/common.h"

// TODO : cling slides down even when on a prop
// TODO : a collision with a prop while clinging breaks physics (for a prop moving in the y dir at least)
namespace hero
{
  Cling::Cling(float speed) :
    speed(speed)
  {
    ctr = 0;
    dir = common::Horizontal::NONE;
  }
  
  void Cling::enter(Spirit& spirit,
			 const stage::Zone& zone,
			 const enemy::EnemyVec& enemies,
			 const prop::PropVec& props)
  {
    ctr = 0;
    dir = spirit.orientation.h;
  }

  void Cling::input(Spirit& spirit,
			 const stage::Zone& zone,
			 const enemy::EnemyVec& enemies,
			 const prop::PropVec& props)
  {
    if (spirit.controller->is_pressed(input::Glyph::A)) {
      if (dir == common::Horizontal::LEFT) {
	spirit.orientation.h = common::Horizontal::RIGHT;
	spirit.force.set_vx(speed);
	
      } else if (dir == common::Horizontal::RIGHT) {
	spirit.orientation.h = common::Horizontal::LEFT;
	spirit.force.set_vx(-speed);
      }
      spirit.motion_flag.set(static_cast<int>(MotionState::JUMP_AWAY));
    }
  }

  void Cling::update(Spirit& spirit,
			  const stage::Zone& zone,
			  const enemy::EnemyVec& enemies,
			  const prop::PropVec& props)
  {
    bool x_collision = false;
    if (spirit.controller->is_on(input::Glyph::LEFT)) {
      spirit.orientation.h = common::Horizontal::LEFT;
      x_collision = spirit.mass.is_sidled_left(zone);
      
    } else if (spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.orientation.h = common::Horizontal::RIGHT;
      x_collision = spirit.mass.is_sidled_right(zone);
    }

    spirit.mass.update_x(0);

    if (!x_collision) {
      ctr++;
    }

    // TODO : do not add like this
    spirit.force.add_y(-0.5);

    bool collision = move_y(zone, props, spirit);

    if (collision) {
      spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
      
    } else if (!spirit.mass.is_sidled(zone)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
      
    } else if (ctr >= 10) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }
}
