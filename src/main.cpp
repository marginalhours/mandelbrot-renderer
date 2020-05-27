#include "input.h"
#include "mandelbrot.h"
#include "renderer.h"
#include <iostream>

/**
 * Display the help message if the user provides -h / --help as the first
 * argument
 */
void usage() {
  std::cout << "Render Mandelbrot fractals." << std::endl
            << std::endl
            << "Usage: " << std::endl
            << "\t./Mandelbrot [-h/--help] [--screen-width <px>] "
               "[--screen-height <px>]"
            << std::endl
            << std::endl
            << "Optional parameters: " << std::endl
            << "\t-h/--help:"
            << " display this help message and exit" << std::endl
            << "\t-w/--screen-width:"
            << " set screen width in pixels (default: 800)" << std::endl
            << "\t-h/--screen-height:"
            << " set screen height in pixels (default: 600)" << std::endl;
}

/**
 * Sets the screen width and height based on user inputs if present
 */
void setScreenDimensions(unsigned int &screen_width,
                         unsigned int &screen_height, char *argv[], int argc) {
  for (int i = 1; i < argc; i++) {
    if ((std::string(argv[i]) == "--screen-width" ||
         std::string(argv[i]) == "-w") &&
        (i + 1) < argc) {
      screen_width = std::stoi(argv[i + 1]);
    }
  }

  for (int i = 1; i < argc; i++) {
    if ((std::string(argv[i]) == "--screen-height" ||
         std::string(argv[i]) == "-h") &&
        (i + 1) < argc) {
      screen_height = std::stoi(argv[i + 1]);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc > 1 &&
      (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    usage();
    return 0;
  }

  unsigned int screen_width = 800;
  unsigned int screen_height = 600;

  try {
    setScreenDimensions(screen_width, screen_height, argv, argc);
  } catch (...) {
    std::cout << "Error: Please provide integer arguments for screen width and "
                 "height."
              << std::endl;
    return 0;
  }

  unsigned int thread_count = std::thread::hardware_concurrency();

  Renderer renderer(screen_width, screen_height);
  Mandelbrot mandelbrot(screen_width, screen_height, thread_count);
  Input input;

  mandelbrot.run(input, renderer);

  return 0;
}