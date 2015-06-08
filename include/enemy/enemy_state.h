#ifndef __ENEMY_STATE_H__
#define __ENEMY_STATE_H__

#include <memory>
#include <vector>

#include "stage/zone.h"
#include "enemy/enemy_spirit.h"
#include "hero/spirit.h"

namespace enemy
{
  struct EnemyState
  {
    virtual void enter(EnemySpirit&, const stage::Zone&, const hero::Spirit&) { }
    virtual void exit(EnemySpirit&, const stage::Zone&, const hero::Spirit&) { }
    virtual void update(EnemySpirit&, const stage::Zone&, const hero::Spirit&) = 0;
  };

  typedef std::vector<std::unique_ptr<EnemyState>> EnemyStateVec;
}

#endif
