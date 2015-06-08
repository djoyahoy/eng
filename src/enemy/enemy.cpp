#include "enemy/enemy.h"

namespace enemy
{
  Enemy::Enemy(const EnemySpirit& spirit, EnemyStateVec motion) :
    gfx::IPaintable(), motion_states(std::move(motion)), spirit(spirit)
  {
    active = true;
    damaged = false;
    motion_state = 0;
  }

  void Enemy::paint(const gfx::IPainter& painter, float blend) const
  {
    if (!active) {
      return;
    }
    painter.paint_sprite(spirit.mass, spirit.sprite, blend);
  }

  void Enemy::update(const stage::Zone& zone, const hero::Spirit& hero_spirit)
  {
    if (!active) {
      return;
    }

    motion_states[motion_state]->update(spirit, zone, hero_spirit);
    if (spirit.motion_flag.is_set()) {
      motion_states[motion_state]->exit(spirit, zone, hero_spirit);
      motion_state = spirit.motion_flag.get();
      motion_states[motion_state]->enter(spirit, zone, hero_spirit);
    }
  }

  void Enemy::hit(unsigned int dmg)
  {
    if (active && !damaged) {
      damaged = true;
      spirit.hp -= dmg;
      if (spirit.hp <= 0) {
	active = false;
      }
    }
  }

  void Enemy::unhit()
  {
    damaged = false;
  }
}
