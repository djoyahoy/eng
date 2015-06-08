#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <memory>
#include <vector>

#include "stage/zone.h"
#include "enemy/enemy_spirit.h"
#include "enemy/enemy_state.h"
#include "gfx/ipaintable.h"
#include "gfx/ipainter.h"

namespace enemy
{
  // TODO : add damage states for enemies
  class Enemy : public gfx::IPaintable
  {
  protected:
    bool active;
    bool damaged;
    int motion_state;
    EnemyStateVec motion_states;
  public:
    EnemySpirit spirit;
    Enemy(const EnemySpirit&, EnemyStateVec);
    void paint(const gfx::IPainter&, float) const;
    void update(const stage::Zone&, const hero::Spirit&);
    bool is_active() const { return active; }
    void hit(unsigned int);
    void unhit();
  };

  typedef std::vector<std::unique_ptr<Enemy>> EnemyVec;
}

#endif
