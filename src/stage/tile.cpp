#include "json/json.h"
#include "stage/tile.h"

namespace stage
{
  Tile::Tile(TileType type, int index)
  {
    this->type = type;
    this->index = index;
  }

  Tile make_tile(const Json::Value& doc)
  {
    return Tile(static_cast<TileType>(doc["type"].asInt()), doc["index"].asInt());
  }
}
