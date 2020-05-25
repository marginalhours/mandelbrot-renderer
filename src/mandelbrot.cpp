#include "mandelbrot.h"
#include "SDL.h"
#include <complex>
#include <iostream>

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

  while (running) {
    Input.HandleInput(*this);

    if (dirty) {
      std::cout << "Rerendering...";
      std::cout.flush();

      Uint32 frame_start = SDL_GetTicks();

      // recalculate pixels
      recalculate(renderer.getPixels(), renderer.getScreenWidth(),
                  renderer.getScreenHeight());

      // rerender pixels
      renderer.Render();

      Uint32 frame_duration = SDL_GetTicks() - frame_start;

      renderer.UpdateWindowTitle(frame_duration);
      dirty = false;
      std::cout << " done in " << std::to_string(frame_duration) << "ms"
                << std::endl;
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

      unsigned int max_iterations = 50;
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
