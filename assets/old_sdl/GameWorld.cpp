#include "GameWorld.hpp"
#include "InputProcessor.hpp"
#include "Display.hpp"

GameWorld::GameWorld() {
   // Nothing
}

GameWorld::~GameWorld() {
   // Nothing
}

void GameWorld::loadWorld(const char * filename) {
   // Set the filename
   _filename = filename;

   // Load stanard things
   _pRenderer = globalDisplay->getRenderer();

   // Load the level data
   _loadWorldData();
}

void GameWorld::startWorld() {
   bool done = false;

   // Start the timer
   _gameTimer.start();

   while (!done) {
      // Update the game timer
      _gameTimer.update();
      _delta = _gameTimer.getDelta();
      _framerate.update(_delta);

      // Process events
      globalInputProcessor->processEvents();

      // Run the level loop
      done = _worldLoop();

      // Present the surface
      SDL_RenderPresent(_pRenderer);
   }

   // Stop the level timer
   _gameTimer.stop();

   // Destroy the level data
   _destroyWorldData();
}
