#include <vector>
#include "hero/hero.h"
#include "hero/states/attack.h"
#include "hero/states/climb.h"
#include "hero/states/cling.h"
#include "hero/states/damaged.h"
#include "hero/states/docile.h"
#include "hero/states/explore.h"
#include "hero/states/fall.h"
#include "hero/states/healthy.h"
#include "hero/states/idle.h"
#include "hero/states/invulnerable.h"
#include "hero/states/jump.h"
#include "hero/states/jump_away.h"
#include "hero/states/roll.h"
#include "hero/states/walk.h"

namespace hero
{
  Hero::Hero(const Spirit& spirit,
	     std::vector<std::unique_ptr<State>> motion,
	     std::vector<std::unique_ptr<State>> action,
	     std::vector<std::unique_ptr<State>> damage) :
    gfx::IPaintable(),
    motion_states(std::move(motion)),
    action_states(std::move(action)),
    damage_states(std::move(damage)),
    spirit(spirit)
  {
    motion_state = 0;
    action_state = 0;
    damage_state = 0;
  }

  void Hero::paint(const gfx::IPainter& painter, float blend) const
  {
    if (action_state == 1) {
      if (spirit.orientation.h == common::Horizontal::RIGHT) {
	painter.paint_sprite(spirit.mass.get_a(), spirit.attack_sprite);
      } else {
	physics::Point offset(spirit.attack_sprite.get_width(), 0);
	painter.paint_sprite(spirit.mass.get_d() - offset, spirit.attack_sprite);
      }
    }
    painter.paint_sprite(spirit.mass, spirit.sprite, blend);
  }

  static void update_state(int& cur_state,
			   actor::StateFlag& state_flag,
			   const std::vector<std::unique_ptr<State>>& states,
			   Spirit& spirit,
			   const stage::Zone& zone,
			   const enemy::EnemyVec& enemies,
			   const prop::PropVec& props)
  {
    states[cur_state]->input(spirit, zone, enemies, props);
    if (state_flag.is_set()) {
      states[cur_state]->exit(spirit, zone, enemies, props);
      cur_state = state_flag.get();
      states[cur_state]->enter(spirit, zone, enemies, props);
    }
    states[cur_state]->update(spirit, zone, enemies, props);
    if (state_flag.is_set()) {
      states[cur_state]->exit(spirit, zone, enemies, props);
      cur_state = state_flag.get();
      states[cur_state]->enter(spirit, zone, enemies, props);
    }
  }

  void Hero::update(const stage::Zone& zone,
		    const enemy::EnemyVec& enemies,
		    const prop::PropVec& props)
  {
    // TODO : Create a bound that will be updated in all states.
    //        Update that bound, then set this bound to the heros mass
    //        at the end of this function.
    //
    // TODO : Each state should have its own force obj that gets reset each entry/exit.
    update_state(motion_state, spirit.motion_flag, motion_states, spirit, zone, enemies, props);
    update_state(action_state, spirit.action_flag, action_states, spirit, zone, enemies, props);
    update_state(damage_state, spirit.damage_flag, damage_states, spirit, zone, enemies, props);
  }

  std::unique_ptr<Hero> make_hero(int x,
				  int y,
				  std::shared_ptr<input::Controller> controller)
  {
    actor::Health health(3);
    common::Orientation orientation = {common::Horizontal::RIGHT, common::Vertical::NONE};
    physics::Mass mass({x, y}, 15, 21);
    physics::Bound attack({0, 0}, 48, 32);
    gfx::Sprite sprite(1.0, 0.8, 0.2, 15, 21);
    gfx::Sprite attack_sprite(1.0, 0.4, 0.2, 48, 32);
    Spirit spirit(controller, health, orientation, mass, attack, sprite, attack_sprite);

    std::vector<float> roll_values = {6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2,
				      1, 1, 1, 1, 0.5,  0.5,  0.5,  0.5, 0.25, 0.25,
				      0.25, 0.25, 0, 0, 0, 0};

    std::vector<std::unique_ptr<State>> states;
    states.emplace_back(std::make_unique<Idle>());
    states.emplace_back(std::make_unique<Fall>(3, -10, -0.5));
    states.emplace_back(std::make_unique<Walk>(3));
    states.emplace_back(std::make_unique<Jump>(3, 4, 10));
    states.emplace_back(std::make_unique<Roll>(3, roll_values));
    states.emplace_back(std::make_unique<Cling>(3));
    states.emplace_back(std::make_unique<JumpAway>(3, 4, 2, 10));
    states.emplace_back(std::make_unique<Climb>(1.5));
    states.emplace_back(std::make_unique<Explore>());

    std::vector<std::unique_ptr<State>> actions;
    actions.emplace_back(std::make_unique<Docile>());
    actions.emplace_back(std::make_unique<Attack>(6));

    std::vector<std::unique_ptr<State>> damages;
    damages.emplace_back(std::make_unique<Healthy>());
    damages.emplace_back(std::make_unique<Damaged>(90));
    damages.emplace_back(std::make_unique<Invulnerable>());

    return std::make_unique<Hero>(spirit, std::move(states), std::move(actions), std::move(damages));
  }
}
