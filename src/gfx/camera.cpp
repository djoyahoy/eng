#include "gfx/camera.h"

namespace gfx
{
  int CameraBound::collide_x(const stage::Zone& zone, int dx) const
  {
    if (dx > 0) {
      for (int x = 1; x <= dx; x++) {
	for (int y = get_bottom(); y <= get_top() - 1; y++) {
	  if (!zone.has_room(get_right() + x -1, y)) {
	    return x - 1;
	  }
	}
      }
    } else if (dx < 0) {
      for (int x = -1; x >= dx; x--) {
	for (int y = get_bottom(); y <= get_top() - 1; y++) {
	  if (!zone.has_room(get_left() + x, y)) {
	    return x + 1;
	  }
	}
      }
    }
    return dx;
  }

  int CameraBound::collide_y(const stage::Zone& zone, int dy) const
  {
    if (dy > 0) {
      for (int y = 1; y <= dy; y++) {
	for (int x = get_left(); x <= get_right() - 1; x++) {
	  if (!zone.has_room(x, get_top() + y - 1)) {
	    return y - 1;
	  }
	}
      }
    } else if (dy < 0) {
      for (int y = -1; y >= dy; y--) {
	for (int x = get_left(); x <= get_right() - 1; x++) {
	  if (!zone.has_room(x, get_bottom() + y)) {
	    return y + 1;
	  }
	}
      }
    }
    return dy;
  }

  Camera::Camera(const CameraBound& bound) : bound(bound)
  {

  }

  // TODO : fix how camera collides with stage
  // TODO : work with camera LERP until it feels "good"
  // TODO : add camera zoom
  void Camera::update(const stage::Zone& zone, const hero::Hero& hero)
  {
    auto change = hero.spirit.mass.get_center() - bound.get_center();

    int lead = 0;
    if (hero.spirit.orientation.h == common::Horizontal::RIGHT) {
      lead = 4;
    } else {
      lead = -4;
    }

    force.add_x((static_cast<float>(change.x) / 16) + lead);
    //int dx = bound.collide_x(zone, force.get_dx());
    int dx = force.get_dx();
    bound.update_x(dx);

    // TODO : use ceil
    force.add_y((static_cast<float>(change.y) / 8) + 4);
    //int dy = bound.collide_y(zone, force.get_dy());
    int dy = force.get_dy();
    bound.update_y(dy);
  }
}
