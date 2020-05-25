#ifndef INPUT_H
#define INPUT_H

#include "mandelbrot.h"

// forward declaration for use in function signature
class Mandelbrot;

class Input {
public:
  void HandleInput(Mandelbrot &instance) const;
};

#endif