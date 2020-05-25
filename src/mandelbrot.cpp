#include "mandelbrot.h"
#include "SDL.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>

constexpr int MILLISECONDS_BETWEEN_FRAMES = 1000 / 24;

inline Uint32 colorFromIterations(unsigned int iterations,
                                  unsigned max_iterations) {
  // we use the bernstein polynomials for colouring
  double f = (double)iterations / (double)max_iterations;
  double h = (1 - f);

  int r = (int)(9 * h * f * f * f * 255);
  int g = (int)(15 * h * h * f * f);
  int b = (int)(8.5 * h * h * h * f);

  return 0xff000000 | r << 16 | g << 8 | b;
}

void Mandelbrot::resetBounds() {
  /* reset image bounds */
  zoom = 1.0;
  center_y = 0.0;
  center_x = -1.0;
  setBoundsFromZoom();
}

void Mandelbrot::zoomIn() {
  zoom *= 0.95;
  setBoundsFromZoom();
}

void Mandelbrot::zoomOut() {
  zoom *= 1.05;
  setBoundsFromZoom();
}

void Mandelbrot::moveUp() {
  center_y -= 0.1 * zoom;
  setBoundsFromZoom();
}

void Mandelbrot::moveLeft() {
  center_x -= 0.1 * zoom;
  setBoundsFromZoom();
}

void Mandelbrot::moveDown() {
  center_y += 0.1 * zoom;
  setBoundsFromZoom();
}

void Mandelbrot::moveRight() {
  center_x += 0.1 * zoom;
  setBoundsFromZoom();
}

void Mandelbrot::increaseIterations() {
  max_iterations += 10;
  dirty = true;
}

void Mandelbrot::decreaseIterations() {
  if (max_iterations > 0) {
    max_iterations -= 10;
    dirty = true;
  }
}

void Mandelbrot::onMouseDown(int x, int y) {
  selection.x = x;
  selection.y = y;
  selection.w = 0;
  selection.h = 0;

  dragging = true;
}

void Mandelbrot::onMouseUp(int x, int y) {
  int x_start = std::min(x, selection.x);
  int x_end = std::max(x, selection.x);
  int y_start = std::min(y, selection.y);
  int y_end = std::max(y, selection.y);

  int x_mid = x_start + ((float)(x_end - x_start) / 2.0);
  int y_mid = y_start + ((float)(y_end - y_start) / 2.0);

  // get new center
  center_x = min_x + (((float)x_mid / (float)screen_width) * (max_x - min_x));
  center_y = min_y + (((float)y_mid / (float)screen_height) * (max_y - min_y));

  // set zoom based on hypotenuse of zoom rectangle
  double zoom_hypotenuse = sqrt((x_end - x_start) * (x_end - x_start) +
                                (y_end - y_start) * (y_end - y_start));
  double window_hypotenuse =
      sqrt(screen_width * screen_width + screen_height * screen_height);

  zoom *= zoom_hypotenuse / window_hypotenuse;

  // Set bounds based on new center and zoom
  setBoundsFromZoom();

  // reset selection rectangle to nothing
  selection.x = 0;
  selection.y = 0;
  selection.w = 0;
  selection.h = 0;

  dragging = false;
  dirty = true;
}

void Mandelbrot::onMouseMove(int x, int y) {
  if (dragging) {
    selection.w = x - selection.x;
    selection.h = y - selection.y;
  }
}

void Mandelbrot::setBoundsFromZoom() {
  min_x = center_x - (zoom * (x_range / 2.0));
  max_x = center_x + (zoom * (x_range / 2.0));
  min_y = center_y - (zoom * (y_range / 2.0));
  max_y = center_y + (zoom * (y_range / 2.0));

  dirty = true;
}

void Mandelbrot::stop() { running = false; }

void Mandelbrot::run(Input const &Input, Renderer &renderer) {

  running = true;

  Uint32 prev_frame_end = SDL_GetTicks();

  while (running) {
    Input.HandleInput(*this);

    Uint32 frame_start = SDL_GetTicks();

    if (dirty) {
      /* if the dirty flag is set, we must recalculate the colour values
      for each pixel */
      recalculate(renderer.getPixels(), renderer.getScreenWidth(),
                  renderer.getScreenHeight());

      Uint32 calculate_duration = SDL_GetTicks() - frame_start;

      renderer.updateWindowTitle(calculate_duration);
      dirty = false;
    }

    /* Refresh the screen periodically -- useful for showing thread progress */
    if (SDL_GetTicks() - prev_frame_end > MILLISECONDS_BETWEEN_FRAMES) {
      renderer.render(selection);
      prev_frame_end = SDL_GetTicks();
    }
  }
}

void Mandelbrot::recalculate(std::vector<Uint32> &pixels,
                             unsigned int screen_width,
                             unsigned int screen_height) {

  for (auto j = 0; j < screen_height; j++) {
    for (auto i = 0; i < screen_width; i++) {
      std::complex<double> c{
          min_x + (((double)i / screen_width) * (max_x - min_x)),
          min_y + (((double)j / screen_height) * (max_y - min_y))};

      std::complex<double> z{0, 0};

      unsigned int iteration = 0;

      for (iteration = 0; iteration < max_iterations; iteration++) {
        z = (z * z) + c;

        if (abs(z) >= 2.0) {
          break;
        }
      }

      if (iteration == max_iterations) {
        pixels[(screen_width * j) + i] = 0xff000000;
      } else {
        pixels[(screen_width * j) + i] =
            colorFromIterations(iteration, max_iterations);
      }
    }
  }
}
