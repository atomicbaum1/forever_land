#include "SDLIncludes.hpp"
#include "GameEngine.hpp"
#include "Settings.hpp"
#include "Logger.hpp"
#include "GameException.hpp"

void GameEngine::GameEngineInputProcessor::keyboardEvent(SDL_KeyboardEvent * keyboardEvent) {
   const Uint8 * key = SDL_GetKeyboardState(NULL);

   switch (keyboardEvent->state) {
   case SDL_PRESSED:
      switch (keyboardEvent->keysym.sym) {
      case SDLK_ESCAPE:
         exit(0);
         break; // Useless but makes the compiler happy

      default:
         break;
      }
      break;

   case SDL_RELEASED:
      break;

   default:
      break;
   }
}

void GameEngine::GameEngineInputProcessor::quitEvent(SDL_QuitEvent * quitEvent) {
   exit(1);
}

GameEngine::GameEngine() {
   try {
      // Start the logger
      globalLogger->openLogFile();
      globalLogger->setLogLevel(LogLevel_Info | LogLevel_Debug | LogLevel_Error);
      globalLogger->logInfo("Starting the game engine");

      // Init the game settings
      globalSettings->loadSettings(DEFAULT_SETTINGS_NAME);
      globalSettings->applyLoadSettings();

      // Register for input
      globalInputProcessor->registerForKeyboardEvent(&_gameEngineInputProcessor);
      globalInputProcessor->registerForQuitEvent(&_gameEngineInputProcessor);
   }
   catch (GameException & exception) {
      std::string exceptionString;
      exception.getExceptionString(exceptionString);
      globalLogger->logError(exceptionString);
      SDL_assert(0);
   }

}

GameEngine::~GameEngine() {
   // Stop the Game
}

void GameEngine::turnKey(GameWorld * gameWorld) {
   // Load the world data
   gameWorld->loadWorld(globalSettings->getStartingWorld());

   // Start eveything
   gameWorld->startWorld();
}
