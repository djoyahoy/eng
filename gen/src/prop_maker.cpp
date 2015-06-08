#include "prop_maker.h"

#include <unordered_map>

#include "json/json.h"



namespace prop
{
  static std::unordered_map<std::string, std::function<std::unique_ptr<Prop>(const Json::Value&)>> maker_map = {};

  std::function<std::unique_ptr<Prop>(const Json::Value&)> get_prop_maker(std::string key)
  {
    return maker_map[key];
  }
}
