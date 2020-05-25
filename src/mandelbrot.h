#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "SDL.h"
#include "input.h"
#include "renderer.h"
#include <future>
#include <random>

// forward declaration for use in function signature
class Input;

// A RenderOptions object contains information for redrawing a region of the
// image on the canvas.
struct RenderOptions {
  unsigned int first_row; /* first row of pixels to calculate */
  unsigned int last_row;  /* last row of pixels to calculate */
  unsigned int max_iterations;
  unsigned int screen_width;
  unsigned int screen_height;
  double x_min;
  double x_max;
  double y_min;
  double y_max;
};

class Mandelbrot {
public:
  Mandelbrot(unsigned int screen_width, unsigned int screen_height)
      : screen_width(screen_width), screen_height(screen_height) {
    resetBounds();
  };

  void run(Input const &input, Renderer &renderer);

  void resetBounds();
  void zoomIn();
  void zoomOut();
  void stop();
  void moveUp();
  void moveLeft();
  void moveDown();
  void moveRight();
  void onMouseDown(int x, int y);
  void onMouseUp(int x, int y);
  void onMouseMove(int x, int y);
  void increaseIterations();
  void decreaseIterations();

private:
  // screen size
  unsigned int screen_width;
  unsigned int screen_height;

  // bounds in the complex plane
  double x_range = 3.0;
  double y_range = 2.5;
  double center_x = -1.0;
  double center_y = 0.0;
  double x_min = -2.5;
  double x_max = 0.5;
  double y_min = -1.25;
  double y_max = 1.25;
  double zoom = 1.0;

  // rendering threads
  std::vector<std::future<void>> render_threads;

  // maximum iterations
  unsigned int max_iterations = 50;

  // selection rectangle
  SDL_Rect selection{0, 0, 0, 0};

  // flag for if still running
  bool running;
  // flag for redraw on next frame;
  bool dirty;
  // flag for mouse dragging
  bool dragging{false};

  // method: recalculate colour of each pixel
  void recalculate(std::vector<Uint32> &pixels, unsigned int screen_width,
                   unsigned int screen_height);

  void setBoundsFromState();
};

#endif