#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "SDL.h"
#include "input.h"
#include "renderer.h"
#include <future>
#include <random>

// forward declaration for use in function signature
class Input;

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
  double min_x = -2.5;
  double max_x = 0.5;
  double min_y = -1.25;
  double max_y = 1.25;
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

  // method: recalculate colours of pixels within a specific y-range
  void updatePixelsInRange(std::vector<Uint32> &pixels, unsigned int start_row,
                           unsigned int end_rows);

  void setBoundsFromState();
};

#endif