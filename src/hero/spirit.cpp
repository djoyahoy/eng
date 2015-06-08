#include "hero/spirit.h"

namespace hero
{
  // TODO : create a link object
  Spirit::Spirit(std::shared_ptr<input::Controller> controller,
		 const actor::Health& health,
		 const common::Orientation& orientation,
		 const physics::Mass& mass,
		 const physics::Bound& attack,
		 const gfx::Sprite& sprite,
		 const gfx::Sprite& attack_sprite) :
    controller(controller),
    health(health),
    orientation(orientation),
    mass(mass),
    sprite(sprite),
    attack(attack),
    attack_sprite(attack_sprite)
  {
    link = nullptr;
  }
}
