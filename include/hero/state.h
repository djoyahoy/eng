#ifndef __HERO_STATE_H__
#define __HERO_STATE_H__

#include <memory>
#include <vector>
#include "stage/zone.h"
#include "enemy/enemy.h"
#include "hero/spirit.h"
#include "prop/prop.h"

namespace hero
{
  enum class MotionState : int
  {
    IDLE,
    FALL,
    WALK,
    JUMP,
    ROLL,
    CLING,
    JUMP_AWAY,
    CLIMB,
    EXPLORE
  };

  enum class ActionState : int
  {
    DOCILE,
    ATTACK
  };
  
  enum class DamageState : int
  {
    HEALTHY,
    DAMAGED,
    INVULNERABLE
  };
  
  class State
  {
  public:
    virtual ~State() {}
    virtual void enter(Spirit&, const stage::Zone&, const enemy::EnemyVec&, const prop::PropVec&) { }
    virtual void exit(Spirit&, const stage::Zone&, const enemy::EnemyVec&, const prop::PropVec&) { }
    virtual void input(Spirit&, const stage::Zone&, const enemy::EnemyVec&, const prop::PropVec&) { }
    virtual void update(Spirit&, const stage::Zone&, const enemy::EnemyVec&, const prop::PropVec&) { }
  };
}

#endif
