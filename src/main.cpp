#include "input.h"
#include "mandelbrot.h"
#include "renderer.h"
#include <iostream>

int main() {
  unsigned int screen_width = 800;
  unsigned int screen_height = 600;
  unsigned int thread_count = std::thread::hardware_concurrency();

  Renderer renderer(screen_width, screen_height);
  Mandelbrot mandelbrot(screen_width, screen_height, thread_count);
  Input input;

  mandelbrot.run(input, renderer);

  return 0;
}