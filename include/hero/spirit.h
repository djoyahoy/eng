#ifndef __HERO_SPIRIT_H__
#define __HERO_SPIRIT_H__

#include "actor/health.h"
#include "actor/spirit.h"
#include "actor/state_flag.h"
#include "common/orientation.h"
#include "gfx/sprite.h"
#include "physics/bound.h"
#include "physics/force.h"
#include "physics/mass.h"
#include "input/controller.h"

namespace hero
{
  struct Spirit
  {
    std::shared_ptr<input::Controller> controller;

    actor::Health health;

    common::Orientation orientation;

    actor::StateFlag motion_flag;
    actor::StateFlag action_flag;
    actor::StateFlag damage_flag;

    physics::Force force;
    physics::Mass mass;
    gfx::Sprite sprite;

    physics::Bound attack;
    gfx::Sprite attack_sprite;
    
    const actor::Spirit* link;
    
    Spirit(std::shared_ptr<input::Controller>,
	   const actor::Health&,
	   const common::Orientation&,
	   const physics::Mass&,
	   const physics::Bound&,
	   const gfx::Sprite&,
	   const gfx::Sprite&);
    };
}

#endif
