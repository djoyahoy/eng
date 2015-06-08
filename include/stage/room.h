#ifndef __ROOM_H__
#define __ROOM_H__

#include <memory>
#include <vector>

#include "common/defines.h"
#include "gfx/ipaintable.h"
#include "json/json-forwards.h"
#include "gfx/sprite.h"
#include "stage/tile.h"

namespace stage
{
  typedef std::vector<std::vector<Tile>> TileGrid;

  class Room : public gfx::IPaintable
  {
  private:
    gfx::SpriteVec sprites;
    TileGrid tiles;
  public:
    Room(const gfx::SpriteVec&, const TileGrid&);
    TileType get_tile(int, int) const;
    void paint(const gfx::IPainter&, float) const;
  };

  std::unique_ptr<Room> make_room(const Json::Value&);
}

#endif
