#include "physics/mass.h"

#include "stage/tile.h"

// TODO : Lots of room for optimization. Sweeping can sweep on tile precision rather
//        than pixel precision for non-testing side (ie. sweep_x can use tiles for y).
//        The overlap func can use tiles rather than for pixels for entire sweep.
namespace physics
{
  bool Mass::sweep_x(const stage::Zone& zone, int& dx) const
  {
    if (dx > 0) {
      for (int x = 1; x <= dx; x++) {
	for (int y = get_bottom(); y <= get_top() - 1; y++) {
	  stage::TileType tile = zone.get_tile(get_right() + (x - 1), y);
	  if (tile == stage::TileType::SOLID) {
	    dx = x - 1;
	    return true;
	  }
	}
      }
    } else if (dx < 0) {
      for (int x = -1; x >= dx; x--) {
	for (int y = get_bottom(); y <= get_top() - 1; y++) {
	  stage::TileType tile = zone.get_tile(get_left() + x, y);
	  if (tile == stage::TileType::SOLID) {
	    dx = x + 1;
	    return true;
	  }
	}
      }
    }
    return false;
  }

  bool Mass::sweep_y(const stage::Zone& zone, int& dy) const
  {
    if (dy > 0) {
      for (int y = 1; y <= dy; y++) {
	for (int x = get_left(); x <= get_right() - 1; x++) {
	  stage::TileType tile = zone.get_tile(x, get_top() + (y - 1));
	  if (tile == stage::TileType::SOLID) {
	    dy = y - 1;
	    return true;
	  }
	}
      }
    } else if (dy < 0) {
      for (int y = -1; y >= dy; y--) {
	for (int x = get_left(); x <= get_right() - 1; x++) {
	  stage::TileType tile = zone.get_tile(x, get_bottom() + y);
	  if (tile == stage::TileType::SOLID) {
	    dy = y + 1;
	    return true;
	  } else if (tile == stage::TileType::LADDER_TOP &&
		     zone.get_tile(x, get_bottom() + y + 1) != stage::TileType::LADDER_TOP) {
	    dy = y + 1;
	    return true;
	  }
	}
      }
    }
    return false;
  }

  bool Mass::sweep_ground(const stage::Zone& zone, int& dx) const
  {
    if (dx > 0) {
      for (int x = 1; x <= dx; x++) {
	stage::TileType tile = zone.get_tile(get_right() + (x - 1), get_bottom() - 1);
	if (tile == stage::TileType::EMPTY) {
	  dx = x - 1;
	  return true;
	}
      }
    } else if (dx < 0) {
      for (int x = -1; x >= dx; x--) {
	stage::TileType tile = zone.get_tile(get_left() + x, get_bottom() - 1);
	if (tile == stage::TileType::EMPTY) {
	  dx = x + 1;
	  return true;
	}
      }
    }
    return false;
  }

  bool Mass::sweep_ladder(const stage::Zone& zone, int x, int& dy) const
  {
    if (dy > 0) {
      for (int y = 1; y <= dy; y++) {
	stage::TileType top_tile = zone.get_tile(x, get_top() + (y - 1));
	stage::TileType bot_tile = zone.get_tile(x, get_bottom() + y);
	if (top_tile == stage::TileType::SOLID) {
	  dy = y;
	  return true;
	} else if (bot_tile != stage::TileType::LADDER &&
		   bot_tile != stage::TileType::LADDER_TOP &&
		   top_tile != stage::TileType::LADDER) {
	  dy = y;
	  return false;
	}
      }
    } else if (dy < 0) {
      for (int y = -1; y >= dy; y--) {
	stage::TileType top_tile = zone.get_tile(x, get_top() + (y - 1));
	stage::TileType bot_tile = zone.get_tile(x, get_bottom() + y);
	if (bot_tile == stage::TileType::SOLID) {
	  dy = y;
	  return false;
	} else if (top_tile != stage::TileType::LADDER &&
		   top_tile !=stage::TileType::LADDER_TOP &&
		   bot_tile != stage::TileType::LADDER_TOP) {
	  dy = y;
	  return false;
	}
      }
    }
    return true;
  }

  bool Mass::is_grounded(const stage::Zone& zone) const
  {
    for (int x = get_left(); x <= get_right() - 1; x++) {
      stage::TileType tile = zone.get_tile(x, get_bottom() - 1);
      if (tile == stage::TileType::SOLID) {
	return true;
      } else if (tile == stage::TileType::LADDER_TOP &&
		 zone.get_tile(x, get_bottom()) != stage::TileType::LADDER_TOP) {
	return true;
      }
    }
    return false;
  }

  bool Mass::is_sidled(const stage::Zone& zone) const
  {
    return is_sidled_left(zone) || is_sidled_right(zone);
  }

  bool Mass::is_sidled_left(const stage::Zone& zone) const
  {
    for (int y = get_bottom(); y <= get_top() - 1; y++) {
      stage::TileType tile = zone.get_tile(get_left() - 1, y);
      if (tile == stage::TileType::SOLID) {
	return true;
      }
    }
    return false;
  }

  bool Mass::is_sidled_right(const stage::Zone& zone) const
  {
    for (int y = get_bottom(); y <= get_top() - 1; y++) {
      stage::TileType tile = zone.get_tile(get_right(), y);
      if (tile == stage::TileType::SOLID) {
	return true;
      }
    }
    return false;
  }

  // TODO : could add get_quarter method to mass to limit how much of mass overlaps a ladder (for shifting later)
  bool Mass::overlap_ladder_up(const stage::Zone& zone) const
  {
    for (int x = get_left(); x <= get_right() - 1; x++) {
      for (int y = get_bottom(); y <= get_top() - 1; y++) {
	stage::TileType tile = zone.get_tile(x, y);
	if (tile == stage::TileType::LADDER ||
	    tile == stage::TileType::LADDER_TOP) {
	  return true;
	}
      }
    }
    return false;
  }

  bool Mass::overlap_ladder_down(const stage::Zone& zone) const
  {
    for (int x = get_left(); x <= get_right() - 1; x++) {
      stage::TileType tile = zone.get_tile(x, get_bottom() - 1);
      if (tile == stage::TileType::LADDER ||
	  tile == stage::TileType::LADDER_TOP) {
	return true;
      }
    }
    return false;
  }

  int Mass::ladder_pos_up(const stage::Zone& zone) const
  {
    for (int x = get_left(); x <= get_right() - 1; x++) {
      for (int y = get_bottom(); y <= get_top() - 1; y++) {
	stage::TileType tile = zone.get_tile(x, y);
	if (tile == stage::TileType::LADDER ||
	    tile == stage::TileType::LADDER_TOP) {
	  return x;
	}
      }
    }
    return 0;
  }

  int Mass::ladder_pos_down(const stage::Zone& zone) const
  {
    for (int x = get_left(); x <= get_right() - 1; x++) {
      stage::TileType tile = zone.get_tile(x, get_bottom() - 1);
      if (tile == stage::TileType::LADDER ||
	  tile == stage::TileType::LADDER_TOP) {
	return x;
      }
    }
    return 0;
  }

  bool Mass::overlap_ground(const Mass& other) const
  {
    bool overlap_x = true;
    if (get_right() <= other.get_left() ||
	get_left() >= other.get_right()) {
      overlap_x = false;
    } 

    bool overlap_y = ((get_bottom() >= other.get_top()) &&
		      (get_bottom() - 1 < other.get_top()));

    return overlap_x && overlap_y;
  }
}
