#include "hero/states/common.h"
#include "hero/states/roll.h"

// TODO : fix rolling and damge sprite changes
// TODO : finish roll even when falling
// TODO : consider allowing to early jump out of a rool to improve
//        responsiveness and "good feel"
namespace hero
{
  Roll::Roll(float speed, const std::vector<float>& values) :
    speed(speed),
    ctr(values.size()),
    values(values)
  {
    
  }

  void Roll::enter(Spirit& spirit,
		   const stage::Zone& zone,
		   const enemy::EnemyVec& enemies,
		   const prop::PropVec& props)
  {
    ctr.reset();
    spirit.sprite.set_rgb(1.0, 0.6, 0.6);
    spirit.damage_flag.set(static_cast<int>(DamageState::INVULNERABLE));
  }

  void Roll::exit(Spirit& spirit,
		  const stage::Zone& zone,
		  const enemy::EnemyVec& enemies,
		  const prop::PropVec& props)
  {
    spirit.sprite.set_rgb(1.0, 0.8, 0.2);
    spirit.damage_flag.set(static_cast<int>(DamageState::HEALTHY));
  }


  void Roll::update(Spirit& spirit,
		    const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    if (spirit.orientation.h == common::Horizontal::LEFT) {
      spirit.force.add_x(-values[ctr.value()]);
      
    } else if (spirit.orientation.h == common::Horizontal::RIGHT) {
      spirit.force.add_x(values[ctr.value()]);
    }

    move_x(zone, props, spirit);

    move_y(zone, props, spirit);
  
    if (!check_ground(zone, props, spirit)) {
      if (spirit.orientation.h == common::Horizontal::LEFT) {
	spirit.force.set_vx(-speed);
	
      } else if (spirit.orientation.h == common::Horizontal::RIGHT) {
	spirit.force.set_vx(speed);
      }

      if (spirit.link != nullptr) {
	// Prevent stickiness when attached to a prop.
	spirit.mass.update_y(-1);
      }
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
      
    } else if(spirit.controller->is_pressed(input::Glyph::A)) {
      spirit.force.reset();
      spirit.motion_flag.set(static_cast<int>(MotionState::JUMP));
      
    } else if (ctr.update()) {
      spirit.force.reset();
      
      if(spirit.controller->is_pressed(input::Glyph::A)) {
	spirit.motion_flag.set(static_cast<int>(MotionState::JUMP));
	
      } else if (spirit.controller->is_on(input::Glyph::LEFT) ||
		 spirit.controller->is_on(input::Glyph::RIGHT)) {
	spirit.motion_flag.set(static_cast<int>(MotionState::WALK));
	
      } else {
	spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
      }
    }
  }
}
