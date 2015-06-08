#include "hero/states/climb.h"
#include "hero/states/common.h"

// TODO : disable attack?
// TODO : handle prop collisions?
namespace hero
{
  Climb::Climb(float speed) : speed(speed)
  {

  }

  void Climb::enter(Spirit& spirit,
			 const stage::Zone& zone,
			 const enemy::EnemyVec& enemies,
			 const prop::PropVec& props)
  {
    spirit.force.reset();
    if (spirit.controller->is_on(input::Glyph::UP)) {
      shift_hero(spirit, spirit.mass.ladder_pos_up(zone));
      
    } else if (spirit.controller->is_on(input::Glyph::DOWN)) {
      shift_hero(spirit, spirit.mass.ladder_pos_down(zone));
    }
  }

  void Climb::input(Spirit& spirit,
			 const stage::Zone& zone,
			 const enemy::EnemyVec& enemies,
			 const prop::PropVec& props)
  {
    if (spirit.controller->is_pressed(input::Glyph::A)) {
      spirit.motion_flag.set(static_cast<int>(MotionState::FALL));
    }
  }

  void Climb::update(Spirit& spirit,
			  const stage::Zone& zone,
			  const enemy::EnemyVec& enemies,
			  const prop::PropVec& props)
  {
    if (spirit.controller->is_on(input::Glyph::LEFT)) {
      spirit.orientation.h = common::Horizontal::LEFT;
      
    } else if (spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.orientation.h = common::Horizontal::RIGHT;
    }

    // TODO : this is dumb
    spirit.mass.update_x(0);

    if (spirit.controller->is_on(input::Glyph::UP)) {
      spirit.force.add_y(speed);
      
    } else if (spirit.controller->is_on(input::Glyph::DOWN)) {
      spirit.force.add_y(-speed);
    }

    int dy = spirit.force.get_dy();
    bool climb = spirit.mass.sweep_ladder(zone, spirit.mass.get_center().x, dy);
    spirit.mass.update_y(dy);

    if (!climb) {
      spirit.motion_flag.set(static_cast<int>(MotionState::IDLE));
    }
  }
}
