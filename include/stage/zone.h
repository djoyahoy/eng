#ifndef __ZONE_H__
#define __ZONE_H__

#include <memory>
#include <unordered_map>

#include "common/defines.h"
#include "gfx/ipaintable.h"
#include "json/json-forwards.h"
#include "stage/room.h"

namespace stage
{
  struct RoomKey {
    int row;
    int col;
  };

  struct RoomKeyHash {
    std::size_t operator()(const RoomKey& k) const
    {
      return MAX_ZONE_SIZE * k.row + k.col;
    }
  };

  struct RoomKeyEqual{
    bool operator()(const RoomKey& a, const RoomKey& b) const
    {
      return a.row == b.row && a.col == b.col;
    }
  };

  typedef std::unordered_map<RoomKey, std::unique_ptr<Room>, RoomKeyHash, RoomKeyEqual> RoomDict;

  class Zone : public gfx::IPaintable
  {
  private:
    RoomDict rooms;
  public:
    Zone(RoomDict);
    TileType get_tile(int, int) const;
    bool has_room(int, int) const;
    void paint(const gfx::IPainter&, float) const;
  };

  std::unique_ptr<Zone> make_zone(const Json::Value&);
}

#endif
