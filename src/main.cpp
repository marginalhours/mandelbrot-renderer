#include "input.h"
#include "mandelbrot.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kScreenWidth{800};
  constexpr std::size_t kScreenHeight{600};

  Renderer renderer(kScreenWidth, kScreenHeight);
  Input Input;
  Mandelbrot mandelbrot;
  mandelbrot.Run(Input, renderer);
  return 0;
}