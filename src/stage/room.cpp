#include <stdexcept>

#include "common/defines.h"
#include "json/json.h"
#include "stage/room.h"

namespace stage
{
  Room::Room(const gfx::SpriteVec& sprites, const TileGrid& tiles) : sprites(sprites), tiles(tiles)
  {

  }

  TileType Room::get_tile(int x, int y) const
  {
    if (x < 0) {
      x -= TILE_SIZE;
    }
    if (y < 0) {
      y -= TILE_SIZE;
    }
    int row = y / TILE_SIZE;
    int col = x / TILE_SIZE;
    if (row >= 0 && row < tiles.size()) {
      if (col >= 0 && col < tiles[row].size()) {
	return tiles[row][col].type;
      }
    }
    return TileType::SOLID;
  }

  void Room::paint(const gfx::IPainter& painter, float blend) const
  {
    for (int row = 0; row < tiles.size(); row++) {
      for (int col = 0; col < tiles[row].size(); col++) {
	Tile tile = tiles[row][col];
	if (tile.type != TileType::EMPTY) {
	  float x = static_cast<float>(col) * TILE_SIZE;
	  float y = static_cast<float>(row) * TILE_SIZE;
	  painter.paint_sprite(x, y, sprites.at(tile.index));
	}
      }
    }
  }

  std::unique_ptr<Room> make_room(const Json::Value& doc)
  {
    if (!doc.isMember("sprites")) {
      throw std::runtime_error("No member sprites.");
    }
    gfx::SpriteVec sprites;
    for (auto i = doc["sprites"].begin(); i != doc["sprites"].end(); i++) {
      sprites.emplace_back(gfx::make_sprite(*i));
    }
    sprites.shrink_to_fit();

    if (!doc.isMember("tiles")) {
      throw std::runtime_error("No member tiles.");
    }
    std::vector<Tile> tiles;
    for (auto i = doc["tiles"].begin(); i != doc["tiles"].end(); i++) {
      tiles.emplace_back(make_tile(*i));
    }
    tiles.shrink_to_fit();

    if (!doc.isMember("map")) {
      throw std::runtime_error("No member map.");
    }
    TileGrid map;
    for (auto r = doc["map"].begin(); r != doc["map"].end(); r++) {
      std::vector<Tile> row;
      for (auto c = r->begin(); c != r->end(); c++) {
	row.emplace_back(tiles[c->asInt()]);
      }
      row.shrink_to_fit();
      if (row.size() <= 0 || row.size() > ROOM_COLS) {
	throw std::runtime_error("Malformed room column.");
      }
      map.emplace(map.begin(), row);
    }

    if (map.size() <= 0 || map.size() > ROOM_ROWS) {
      throw std::runtime_error("Malformed room row.");
    }
    return std::make_unique<Room>(sprites, map);
  }
}
