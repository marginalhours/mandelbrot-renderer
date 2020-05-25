#include "input.h"
#include "SDL.h"
#include <iostream>

void Input::HandleInput(Mandelbrot &instance) const {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {

    switch (e.type) {

    case SDL_QUIT: {
      instance.stop();
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (e.button.button == SDL_BUTTON_LEFT) {
        instance.onMouseDown(e.button.x, e.button.y);
        break;
      }
      break;
    }
    case SDL_MOUSEMOTION: {
      instance.onMouseMove(e.motion.x, e.motion.y);
      break;
    }
    case SDL_MOUSEBUTTONUP: {
      if (e.button.button == SDL_BUTTON_LEFT) {
        instance.onMouseUp(e.button.x, e.button.y);
      }
      break;
    }

    case SDL_KEYDOWN: {

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
      case SDLK_SPACE: {
        instance.resetBounds();
        break;
      }
      case SDLK_COMMA: {
        instance.decreaseIterations();
        break;
      }
      case SDLK_PERIOD: {
        instance.increaseIterations();
        break;
      }
      }
      break;
    }
    }
  }
}