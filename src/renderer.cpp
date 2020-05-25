#include "renderer.h"
#include <iostream>
#include <memory>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
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
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(sdl_texture);
  SDL_Quit();
}

void Renderer::Render() {
  SDL_Rect block;
  block.w = screen_width;
  block.h = screen_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Texture *framebuffer{};

  // // Render food
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  // block.x = food.x * block.w;
  // block.y = food.y * block.h;
  // SDL_RenderFillRect(sdl_renderer, &block);

  // // Render snake's body
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  // for (SDL_Point const &point : snake.body) {
  //   block.x = point.x * block.w;
  //   block.y = point.y * block.h;
  //   SDL_RenderFillRect(sdl_renderer, &block);
  // }

  // // Render snake's head
  // block.x = static_cast<int>(snake.head_x) * block.w;
  // block.y = static_cast<int>(snake.head_y) * block.h;
  // if (snake.alive) {
  //   SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  // } else {
  //   SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  // }
  // SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(unsigned int render_time) {
  std::string title{"Mandelbrot -- last render " + std::to_string(render_time)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
