#include <iostream>
#include "SDLIncludes.hpp"
#include "MemoryException.hpp"
#include "GameEngine.hpp"
#include "DemoWorld.hpp"
#include "Logger.hpp"

int main(int argc, char **argv) {
   GameEngine * pGameEngine;
   DemoWorld demoWorld;
   
   try {
      pGameEngine = new GameEngine();
      pGameEngine->turnKey(&demoWorld);
   }
   catch (GameException & e) {
      // TODO: log game message
      switch (e.getExceptionSeverity()) {
      case GameExceptionSeverity_Info:
         break;
      case GameExceptionSeverity_Warning:
         break;
      case GameExceptionSeverity_Error:
         break;
      case GameExceptionSeverity_Assert:
         SDL_assert(0);
         break;
      }
   }

   return 0;
}
