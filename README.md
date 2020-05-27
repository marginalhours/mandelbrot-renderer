# Mandelbrot Renderer

This is an interactive C++ renderer of the Mandelbrot set, using SDL for output

## File and class structure

- `main.cpp` -- entry point. instantiates a `Renderer`, an `Input` handler, and a `Mandelbrot` object
- `renderer.cpp` / `renderer.h` -- manages an SDL window for displaying the results
- `input.cpp` / `input.h` -- handles keyboard input from the user to pan and zoom.
- `mandelbrot.cpp` / `mandelbrot.h` -- handles calculating the colour values of the individual screen pixels by offloading chunks of the screen to a collection of rendering threads
- `message_queue.h` -- a templated message queue class for dispatching
  render tasks.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`.

## Command-line flags

The program supports the following command line flags:

- `-h` / `--help`: prints help message and exits
- `wx` / `--screen-width`: sets the image width in pixels
- `-hx` / `--screen-height`: sets the image height in pixels
- `-c` / `--concurrency`: set number of render threads. Default is number of cpu cores.

## Viewer controls:

### Mouse

Click + drag to draw a rectangle to zoom into.

### Keyboard

- <kbd>space</kbd> -- take screenshot
- <kbd>r</kbd> -- reset viewer
- <kbd>+</kbd>/<kbd>=</kbd> -- zoom in
- <kbd>-</kbd> -- zoom out
- <kbd>.</kbd> -- increase detail (iterations)
- <kbd>,</kbd> -- decrease detail (iterations)
- <kbd>↑</kbd>, <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>→</kbd> -- pan image