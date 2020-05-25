#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "SDL.h"
#include "input.h"
#include "renderer.h"
#include <random>

// forward declaration for use in function signature
class Input;

class Mandelbrot {
public:
  void run(Input const &input, Renderer &renderer);

  void resetBounds();
  void zoomIn();
  void zoomOut();
  void stop();
  void moveUp();
  void moveLeft();
  void moveDown();
  void moveRight();

private:
  // bounds in the complex plane
  double x_range = 3.0;
  double y_range = 2.5;
  double center_x = -1.0;
  double center_y = 0.0;
  double min_x = -2.5;
  double max_x = 0.5;
  double min_y = -1.25;
  double max_y = 1.25;
  double zoom = 1.0;

  // flag for if still running
  bool running;
  // flag for redraw on next frame;
  bool dirty;

  // method: recalculate colour of each pixel
  void recalculate(std::vector<Uint32> &pixels, unsigned int screen_width,
                   unsigned int screen_height);

  void setBoundsFromZoom();
};

#endif