#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render();
  void UpdateWindowTitle(unsigned int render_time);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif