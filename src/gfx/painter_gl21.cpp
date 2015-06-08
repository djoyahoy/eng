#include <stdexcept>
#include <string>

#include <SDL_opengl.h>

#include "common/defines.h"
#include "gfx/painter_gl21.h"

namespace gfx
{
  PainterGL21::PainterGL21(SDL_Window* window, SDL_GLContext context) : window(window), context(context)
  {

  }

  PainterGL21::~PainterGL21()
  {
    if (context != nullptr) {
      SDL_GL_DeleteContext(context);
    }

    if (window != nullptr) {
      SDL_DestroyWindow(window);
    }
  }

  void PainterGL21::clear() const
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void PainterGL21::paint_scene() const
  {
    SDL_GL_SwapWindow(window);
  }

  void PainterGL21::push(float x, float y) const
  {
    glPushMatrix();
    glTranslatef(x, y, 0);
  }

  void PainterGL21::push(const physics::Bound& bound, float blend) const
  {
    auto prev  = bound.get_prev();
    auto cur = bound.get_a();
    float rx = static_cast<float>(cur.x) * blend + static_cast<float>(prev.x) * (1.0 - blend);
    float ry = static_cast<float>(cur.y) * blend + static_cast<float>(prev.y) * (1.0 - blend);
    push(-rx, -ry);
  }

  void PainterGL21::pop() const
  {
    glPopMatrix();
  }

  void PainterGL21::paint_sprite(float x, float y, const Sprite& sprite) const
  {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBegin(GL_QUADS);
    glColor3f(sprite.get_red(), sprite.get_green(), sprite.get_blue());
    glVertex2f(0, 0);
    glVertex2f(0, sprite.get_height());
    glVertex2f(sprite.get_width(), sprite.get_height());
    glVertex2f(sprite.get_width(), 0);
    glEnd();
    glPopMatrix();
  }

  void PainterGL21::paint_sprite(const physics::Point& point, const Sprite& sprite) const
  {
    paint_sprite(static_cast<float>(point.x), static_cast<float>(point.y), sprite);
  }

  void PainterGL21::paint_sprite(const physics::Bound& bound, const Sprite& sprite, float blend) const
  {
    auto prev  = bound.get_prev();
    auto cur = bound.get_a();
    float rx = static_cast<float>(cur.x) * blend + static_cast<float>(prev.x) * (1.0 - blend);
    float ry = static_cast<float>(cur.y) * blend + static_cast<float>(prev.y) * (1.0 - blend);
    paint_sprite(rx, ry, sprite);
  }

  std::unique_ptr<PainterGL21> make_painter_gl21(int width, int height)
  {
    SDL_Window* window = SDL_CreateWindow("eng",
					  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					  width, height,
					  SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == nullptr) {
      throw std::runtime_error("Failed to create window. "  + std::string(SDL_GetError()));
    }

    int actual_width, actual_height;
    SDL_GL_GetDrawableSize(window, &actual_width, &actual_height);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
      throw std::runtime_error("Failed to create gl context. " + std::string(SDL_GetError()));
    }

    glViewport(0, 0, actual_width, actual_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, actual_width, 0, actual_height, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(actual_width / MIN_SCREEN_WIDTH, actual_height / MIN_SCREEN_HEIGHT, 1);

    glClearColor(0, 0, 0, 1);

    if (glGetError() != GL_NO_ERROR) {
      throw std::runtime_error("Failed to init gl. " + std::to_string(glGetError()));
    }

    return std::make_unique<PainterGL21>(window, context);
  }
}
