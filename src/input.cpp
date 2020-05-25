#include "input.h"
#include "SDL.h"
#include <iostream>

void Input::HandleInput(Mandelbrot &instance) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      instance.stop();
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP: {
        instance.moveUp();
        break;
      }
      case SDLK_DOWN: {
        instance.moveDown();
        break;
      }
      case SDLK_LEFT: {
        instance.moveLeft();
        break;
      }
      case SDLK_RIGHT: {
        instance.moveRight();
        break;
      }
      case SDLK_PLUS:
      case SDLK_EQUALS: {
        instance.zoomIn();
        break;
      }
      case SDLK_MINUS: {
        instance.zoomOut();
        break;
      }
      case SDLK_ESCAPE: {
        instance.stop();
        break;
      }
      }
    }
  }
}