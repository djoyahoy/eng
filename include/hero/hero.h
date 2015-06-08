#ifndef __HERO_H__
#define __HERO_H__

#include <memory>

#include "input/controller.h"
#include "stage/zone.h"
#include "enemy/enemy.h"
#include "hero/spirit.h"
#include "hero/state.h"
#include "gfx/ipaintable.h"

namespace hero
{
  class Hero : public gfx::IPaintable
  {
  private:
    int motion_state;
    int action_state;
    int damage_state;
    std::vector<std::unique_ptr<State>> motion_states;
    std::vector<std::unique_ptr<State>> action_states;
    std::vector<std::unique_ptr<State>> damage_states;
  public:
    Spirit spirit;
    Hero(const Spirit&,
	 std::vector<std::unique_ptr<State>>,
	 std::vector<std::unique_ptr<State>>,
	 std::vector<std::unique_ptr<State>>);
    void paint(const gfx::IPainter&, float) const;
    void update(const stage::Zone&,
		const enemy::EnemyVec&,
		const prop::PropVec&);
  };

  std::unique_ptr<Hero> make_hero(int, int, std::shared_ptr<input::Controller>);
}

#endif
