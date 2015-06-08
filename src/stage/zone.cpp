#include <stdexcept>

#include "json/json.h"
#include "stage/zone.h"

namespace stage
{
  Zone::Zone(RoomDict rooms) : rooms(std::move(rooms))
  {

  }

  TileType Zone::get_tile(int x, int y) const
  {
    int row = y;
    if (row < 0) {
      row -= ROOM_HEIGHT;
    }
    row /= ROOM_HEIGHT;

    int col = x;
    if (col < 0) {
      col -= ROOM_WIDTH;
    }
    col /= ROOM_WIDTH;

    auto room = rooms.find({row, col});
    if (room != rooms.end()) {
      return room->second->get_tile(x % ROOM_WIDTH, y % ROOM_HEIGHT);
    }

    return TileType::SOLID;
  }

  bool Zone::has_room(int x, int y) const
  {
    int row = y;
    if (row < 0) {
      row -= ROOM_HEIGHT;
    }
    row /= ROOM_HEIGHT;

    int col = x;
    if (col < 0) {
      col -= ROOM_WIDTH;
    }
    col /= ROOM_WIDTH;

    if (rooms.count({row, col})) {
      return true;
    }
    return false;
  }

  void Zone::paint(const gfx::IPainter& painter, float blend) const
  {
    for (auto const& room : rooms) {
      auto pos = room.first;
      painter.push(pos.col * ROOM_WIDTH, pos.row * ROOM_HEIGHT);
      room.second->paint(painter, blend);
      painter.pop();
    }
  }

  std::unique_ptr<Zone> make_zone(const Json::Value& doc)
  {
    if (!doc.isMember("rooms")) {
      throw std::runtime_error("No member rooms.");
    }
    RoomDict rooms;
    for (auto room = doc["rooms"].begin(); room != doc["rooms"].end(); room++) {
      if (!room->isMember("key")) {
	throw std::runtime_error("No member key.");
      }
      if (!((*room)["key"].isMember("row") || (*room)["key"].isMember("col"))) {
	throw std::runtime_error("No member row or col.");
      }
      auto key = RoomKey{(*room)["key"]["row"].asInt(), (*room)["key"]["col"].asInt()};
      if (rooms.count(key) != 0) {
	throw std::runtime_error("Duplicate room key.");
      }
      rooms.emplace(key, make_room((*room)["room"]));
    }
    return std::make_unique<Zone>(std::move(rooms));
  }
}
