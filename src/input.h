#ifndef INPUT_H
#define INPUT_H

#include "mandelbrot.h"

// forward declaration for use in function signature
class Mandelbrot;
class Renderer;

class Input {
public:
  void handleInput(Mandelbrot &instance, Renderer &renderer) const;
};

#endif