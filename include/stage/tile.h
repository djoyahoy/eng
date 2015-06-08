#ifndef __TILE_H__
#define __TILE_H__

#include "common/defines.h"
#include "json/json-forwards.h"

namespace stage
{
  enum class TileType : int
  {
    EMPTY,
      SOLID,
      LADDER,
      LADDER_TOP
      };

  struct Tile
  {
    TileType type;
    int index;
    Tile(TileType, int);
  };

  Tile make_tile(const Json::Value&);
}

#endif
