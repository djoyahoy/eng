#include <stdexcept>

#include "stage/dungeon.h"
#include "enemy_maker.h"
#include "json/json.h"
#include "prop_maker.h"

namespace stage
{
  Dungeon::Dungeon(std::unique_ptr<Zone> zone, enemy::EnemyVec enemies, prop::PropVec props) :
    zone(std::move(zone)), enemies(std::move(enemies)), props(std::move(props))
  {

  }

  std::unique_ptr<Dungeon> make_dungeon(const Json::Value& doc)
  {
    if (!doc.isMember("zone")) {
      throw std::runtime_error("No member zone.");
    }
    std::unique_ptr<Zone> zone = make_zone(doc["zone"]);
  
    // make enemies
    if (!doc.isMember("enemies")) {
      throw std::runtime_error("No member enemies.");
    }
    enemy::EnemyVec enemies;
    for (auto i = doc["enemies"].begin(); i != doc["enemies"].end(); i++) {
      if (!i->isMember("type")) {
	throw std::runtime_error("Enemy has no member type.");
      }
      auto func = enemy::get_enemy_maker((*i)["type"].asString());
      enemies.emplace_back(func(*i));
    }

    // make props
    if (!doc.isMember("props")) {
      throw std::runtime_error("No member props.");
    }
    prop::PropVec props;
    for (auto i = doc["props"].begin(); i != doc["props"].end(); i++) {
      if (!i->isMember("type")) {
	throw std::runtime_error("Prop has no member type.");
      }
      auto func = prop::get_prop_maker((*i)["type"].asString());
      props.emplace_back(func(*i));
    }

    return std::make_unique<Dungeon>(std::move(zone), std::move(enemies), std::move(props));
  }
}
