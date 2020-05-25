#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "SDL.h"
#include "input.h"
#include "renderer.h"
#include <random>

class Mandelbrot {
public:
  void Run(Input const &input, Renderer &renderer);

private:
  bool _dirty;
  void Update();
};

#endif