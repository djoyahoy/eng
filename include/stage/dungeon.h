#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include <memory>

#include "enemy/enemy.h"
#include "json/json-forwards.h"
#include "prop/prop.h"
#include "stage/zone.h"

namespace stage
{
  struct Dungeon
  {
    std::unique_ptr<Zone> zone;
    enemy::EnemyVec enemies;
    prop::PropVec props;
    Dungeon(std::unique_ptr<Zone>, enemy::EnemyVec, prop::PropVec);
  };

  std::unique_ptr<Dungeon> make_dungeon(const Json::Value&);
}

#endif
