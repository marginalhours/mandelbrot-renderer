#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include <memory>
#include <vector>

class Renderer {
public:
  Renderer(unsigned int screen_width, unsigned int screen_height);
  ~Renderer();

  void captureScreenshot();

  void render(SDL_Rect selection);
  void updateWindowTitle(unsigned int iterations, double x_min, double x_max,
                         double y_min, double y_max);

  // get mutable access to pixel data
  std::vector<Uint32> &getPixels() { return pixels; };

  unsigned int getScreenWidth() { return screen_width; }
  unsigned int getScreenHeight() { return screen_height; }

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *sdl_texture;
  // Array of raw pixels from SDL2 -- format is ARGB in one byte each
  std::vector<Uint32> pixels;

  unsigned int screen_width;
  unsigned int screen_height;
};

#endif