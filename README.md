# Mandelbrot Renderer

This is a (keyboard and mouse) interactive C++ renderer of the Mandelbrot set, using SDL for output.
The main thread maintains an array of pixel data in memory. A pool of rendering
threads are passed messages containing a reference to this pixel data and some bounds,
and compute new colour values for the pixels within those bounds as the user provides
new inputs for zoom level, iterations, and so on.

Realistically this parallelises so well only because each pixel value is truly independent
from all the other pixels -- so this work really belongs in a GPU shader rather than
on the CPU. It's fun to see how large the speedup from multithreading can be with the work
truly is parallelisable, though!

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
- `-c` / `--concurrency`: set number of render threads. Default is the number of cpu cores, so
one thread per core.

## Viewer controls:

### Mouse

Click + drag to draw a rectangle to zoom into.

### Keyboard

- <kbd>space</kbd> -- take screenshot (screenshots are saved to `screenshot-<n>.bmp` in the current directory)
- <kbd>r</kbd> -- reset viewer
- <kbd>+</kbd>/<kbd>=</kbd> -- zoom in
- <kbd>-</kbd> -- zoom out
- <kbd>.</kbd> -- increase detail (iterations)
- <kbd>,</kbd> -- decrease detail (iterations)
- <kbd>↑</kbd>, <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>→</kbd> -- pan image

## File and class structure

- `main.cpp` -- entry point. Handles command-line flags, then instantiates a `Renderer`, an `Input` handler, and a `Mandelbrot` object.
- `renderer.cpp` / `renderer.h` -- Defines the `Renderer` class, which manages an SDL window for displaying the results
- `input.cpp` / `input.h` -- Defines the `Input` class, which handles keyboard and mouse input from the user to pan and zoom.
- `mandelbrot.cpp` / `mandelbrot.h` -- Defines the `Mandelbrot` class, which handles calculating the colour values of the individual screen pixels by offloading chunks of the screen to a collection of rendering threads, as well as several renderer helper methods for
- `message_queue.h` -- a templated message queue class for dispatching
  render tasks.

## Rubric points addressed

### Loops, functions, IO

- *The project demonstrates an understanding of C++ functions and control structures.*

See nested for-loop in fractal calcuation (`mandelbrot.cpp` line `31`), while-loop
in screenshot calculation (`renderer.cpp` line `85`).

- *The project reads data from a file and process the data, or the program writes data to a file.*

See screenshot logic in `renderer.cpp` line `72`.

- *The project accepts user input and processes the input.*

See `main.cpp` for command-line flag handling and `input.cpp` for keyboard / mouse event
handling via `SDL2`.

### Memory management

- *The project makes use of references in function declarations*

See `input.cpp` line 5 and `mandelbrot.cpp` line `61`.

- *The project uses destructors appropriately*

See `mandelbrot.cpp` line `72` for a destructor which clears the message queue
and stops the threads. See `renderer.cpp` line `54` for a destructor which frees
heap-allocated memory via SDL library functions.

### Concurrency

- *The project uses multithreading*

See `mandelbrot.h` line `82` and `message_queue.h` in general.

- *A mutex or lock is used in the project*

See `message_queue.h` line `23`

- *A condition variable is used in the project*

See `message_queue.h` line `24`.
