#include "hero/states/common.h"

namespace hero
{
  bool move_x(const stage::Zone& zone, const prop::PropVec& props, Spirit& spirit)
  {
    int dx = spirit.force.get_dx();
    bool collision = spirit.mass.sweep_x(zone, dx);
    spirit.mass.update_x(dx);

    for (const auto &prop : props) {
      if (spirit.link != &prop->spirit && spirit.mass.overlap(prop->spirit.mass)) {
	int overlap = spirit.mass.overlap_x(prop->spirit.mass);
	spirit.mass.update_x(overlap);
      }
    }

    return collision;
  }

  bool move_y(const stage::Zone& zone, const prop::PropVec& props, Spirit& spirit)
  {
    int dy = spirit.force.get_dy();
    bool collision = spirit.mass.sweep_y(zone, dy);
    spirit.mass.update_y(dy);

    for (const auto &prop : props) {
      if (spirit.link != &prop->spirit && spirit.mass.overlap(prop->spirit.mass)) {
	int overlap = spirit.mass.overlap_y(prop->spirit.mass);
	spirit.mass.update_y(overlap);
	collision = true;
      }
    }

    return collision;
  }

  // TODO : could change overlap bound based on direction of spirit
  bool check_climb(Spirit& spirit, const stage::Zone& zone)
  {
    if (spirit.controller->is_on(input::Glyph::UP)) {
      return spirit.mass.overlap_ladder_up(zone);
    } else if (spirit.controller->is_on(input::Glyph::DOWN)) {
      return spirit.mass.overlap_ladder_down(zone);
    }
    return false;
  }

  bool check_ground(const stage::Zone& zone, const prop::PropVec& props, Spirit& spirit)
  {
    bool grounded = spirit.mass.is_grounded(zone);
    for (const auto &prop : props) {
      if (spirit.mass.overlap_ground(prop->spirit.mass)) {
	grounded = true;
	break;
      }
    }
    return grounded;
  }

  void set_horizontal(Spirit& spirit, const float speed)
  {
    if (spirit.controller->is_on(input::Glyph::LEFT)) {
      spirit.orientation.h = common::Horizontal::LEFT;
      spirit.force.add_x(-speed);
      
    } else if (spirit.controller->is_on(input::Glyph::RIGHT)) {
      spirit.orientation.h = common::Horizontal::RIGHT;
      spirit.force.add_x(speed);
    }
  }

  void shift_hero(Spirit& spirit, const int x)
  {
    int dx = ((x - (x % TILE_SIZE)) + (TILE_SIZE / 2)) - spirit.mass.get_center().x;
    spirit.mass.update_x(dx);
  }
}
