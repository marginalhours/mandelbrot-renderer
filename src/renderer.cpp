#include "renderer.h"
#include <filesystem>
#include <iostream>
#include <string>

Renderer::Renderer(unsigned int screen_width, unsigned int screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize." << std::endl;
    std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Mandelbrot Renderer", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (sdl_window == nullptr) {
    std::cerr << "Window could not be created." << std::endl;
    std::cerr << " SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create Renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

  if (sdl_renderer == nullptr) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Texture
  sdl_texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888,
                                  SDL_TEXTUREACCESS_STREAMING, screen_width,
                                  screen_height);

  if (sdl_texture == nullptr) {
    std::cerr << "Texture could not be created." << std::endl;
    std::cerr << " SDL_Error: " << SDL_GetError() << std::endl;
  }

  // Create pixel array
  pixels = std::vector<Uint32>(screen_height * screen_width, 0);

  // initial render (to make screen black);
  render(SDL_Rect{0, 0, 0, 0});
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(sdl_texture);
  SDL_Quit();
}

void Renderer::captureScreenshot() {
  SDL_Surface *screenshot =
      SDL_CreateRGBSurface(0, screen_width, screen_height, 32, 0x00ff0000,
                           0x0000ff00, 0x000000ff, 0xff000000);

  SDL_RenderReadPixels(sdl_renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
                       screenshot->pixels, screenshot->pitch);

  // Figure out the next free screenshot path will be
  unsigned int next_screenshot_slot = 0;
  std::filesystem::path output_path{
      "screenshot-" + std::to_string(next_screenshot_slot) + ".bmp"};

  while (std::filesystem::exists(output_path)) {
    next_screenshot_slot++;
    output_path = std::filesystem::path(
        "screenshot-" + std::to_string(next_screenshot_slot) + ".bmp");
  }

  SDL_SaveBMP(screenshot, output_path.c_str());
  SDL_FreeSurface(screenshot);

  std::cout << "Wrote out " << output_path << std::endl;
}

void Renderer::render(SDL_Rect selection) {

  // Apply pixels vector to texture
  SDL_UpdateTexture(sdl_texture, NULL, &pixels[0],
                    screen_width * sizeof(uint32_t));

  // Clear renderer
  SDL_RenderClear(sdl_renderer);
  // Render texture to screen
  SDL_RenderCopy(sdl_renderer, sdl_texture, NULL, NULL);

  // Render dragging box if present
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 31);
  SDL_RenderFillRect(sdl_renderer, &selection);

  SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 127);
  SDL_RenderDrawRect(sdl_renderer, &selection);

  // Render screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::updateWindowTitle(unsigned int iterations, double x_min,
                                 double x_max, double y_min, double y_max) {
  std::string title{std::to_string(iterations) + " iterations -- top left (" +
                    std::to_string(x_min) + "," + std::to_string(y_min) +
                    ") bottom right (" + std::to_string(x_max) + "," +
                    std::to_string(y_max) + ")"};

  // Change window title to reflect current view
  SDL_SetWindowTitle(sdl_window, title.c_str());

  // Log title also to console for debugging purposes
  std::cout << title << std::endl;
}
