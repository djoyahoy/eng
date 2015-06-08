#ifndef __PAINTER_GL21_H__
#define __PAINTER_GL21_H__

#include <SDL.h>

#include "gfx/ipainter.h"

namespace gfx
{
  class PainterGL21 : public IPainter
  {
  private:
    SDL_Window* window;
    SDL_GLContext context;
  public:
    PainterGL21(SDL_Window*, SDL_GLContext);
    ~PainterGL21();
    void clear() const;
    void paint_scene() const;
    void push(float, float) const;
    void push(const physics::Bound&, float) const;
    void pop() const;
    void paint_sprite(float, float, const Sprite&) const;
    void paint_sprite(const physics::Point&, const Sprite&) const;
    void paint_sprite(const physics::Bound&, const Sprite&, float) const;
  };

  std::unique_ptr<PainterGL21> make_painter_gl21(int, int);
}

#endif
