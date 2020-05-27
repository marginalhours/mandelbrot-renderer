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
            << "\t-wx/--screen-width:"
            << " set screen width in pixels (default: 800)" << std::endl
            << "\t-hx/--screen-height:"
            << " set screen height in pixels (default: 600)" << std::endl
            << "\t-c/--concurrency:"
            << " set concurrency (-1 to disable) (default: #cpu_cores)"
            << std::endl;
}

/**
 * Sets the screen width and height based on user inputs if present
 */
void setScreenDimensions(unsigned int &screen_width,
                         unsigned int &screen_height, int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if ((std::string(argv[i]) == "--screen-width" ||
         std::string(argv[i]) == "-wx") &&
        (i + 1) < argc) {
      screen_width = std::stoi(argv[i + 1]);
    }
  }

  for (int i = 1; i < argc; i++) {
    if ((std::string(argv[i]) == "--screen-height" ||
         std::string(argv[i]) == "-hx") &&
        (i + 1) < argc) {
      screen_height = std::stoi(argv[i + 1]);
    }
  }
}

/**
 * Sets the maximum concurrency based on user inputs if present.
 */
void setConcurrency(unsigned int &max_threads, int argc, char *argv[]) {
  if (max_threads == 0) {
    max_threads = 1;
  }

  for (int i = 1; i < argc; i++) {
    if ((std::string(argv[i]) == "--concurrency" ||
         std::string(argv[i]) == "-c") &&
        (i + 1) < argc) {
      max_threads = std::stoi(argv[i + 1]);
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
    setScreenDimensions(screen_width, screen_height, argc, argv);
  } catch (...) {
    std::cout << "Error: Please provide integer arguments for screen width and "
                 "height."
              << std::endl;
    return 0;
  }

  unsigned int thread_count = std::thread::hardware_concurrency();

  try {
    setConcurrency(thread_count, argc, argv);
  } catch (...) {
    std::cout << "Error. Please provide integer argument for number of "
                 "concurrent render threads"
              << std::endl;
    return 0;
  }

  Renderer renderer(screen_width, screen_height);
  Mandelbrot mandelbrot(screen_width, screen_height, thread_count);
  Input input;

  mandelbrot.run(input, renderer);

  return 0;
}