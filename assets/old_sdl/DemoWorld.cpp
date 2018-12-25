#include "DemoWorld.hpp"
#include "Display.hpp"
#include <sstream>
#include "SDLIncludes.hpp"
#include "TextureFactory.hpp"

/*
 * TODO:
 * -> Add event based system where collisions fire an event that other things in the game world can pick up on
 */

/*
 * Demo world, some of these are bad ways to do things, like we should store the renderer pointer and such instead of asking for it each time.
 */

void DemoWorld::_loadWorldData() {
   globalInputProcessor->registerForKeyboardEvent(this);
   _pBackgroundTexture = globalTextureFactory->checkoutTexture(globalDisplay->getRenderer(), "Background.png");
   _framerate.limitFps(STANDARD_FPS);
}

void DemoWorld::_destroyWorldData() {
   globalTextureFactory->checkinTexture(_pBackgroundTexture);
}

bool DemoWorld::_worldLoop() {
   std::stringstream windowCaption;
   windowCaption << _framerate.getFps();
   SDL_Window * pWindow = globalDisplay->getWindow();
   SDL_SetWindowTitle(pWindow, windowCaption.str().c_str());
   _pBackgroundTexture->render(globalDisplay->getRenderer());
   return false;
}


void DemoWorld::keyboardEvent(SDL_KeyboardEvent * keyboardEvent) {
   const Uint8 * key = SDL_GetKeyboardState(NULL);
   switch (keyboardEvent->state) {
   case SDL_PRESSED:
      switch (keyboardEvent->keysym.sym) {
      case SDLK_UP:
         break;
      case SDLK_LEFT:
         break;
      case SDLK_RIGHT:
         break;
      case SDLK_DOWN:
         break;
      default:
         break;
      }
      break;
#if 0
   case SDL_RELEASED:
      switch (keyboardEvent->keysym.sym) {
      default:
         break;
      }
      break;
#endif
   default:
      break;
   }
}
