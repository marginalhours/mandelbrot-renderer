#include "mandelbrot.h"
#include "SDL.h"
#include <iostream>

void Mandelbrot::Run(Input const &Input, Renderer &renderer) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    Input.HandleInput(running);
    Update();
    renderer.Render();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;
    renderer.UpdateWindowTitle(frame_count);
  }
}

void Mandelbrot::Update() {}
