#include "enemy_maker.h"

#include <unordered_map>

#include "json/json.h"



namespace enemy
{
  static std::unordered_map<std::string, std::function<std::unique_ptr<Enemy>(const Json::Value&)>> maker_map = {};

  std::function<std::unique_ptr<Enemy>(const Json::Value&)> get_enemy_maker(std::string key)
  {
    return maker_map[key];
  }
}
