#ifndef __GAME_ENGINE_HPP__
#define __GAME_ENGINE_HPP__

#include "InputProcessor.hpp"
#include "GameTimer.hpp"
#include "GameWorld.hpp"

class GameEngine {
private:
   class GameEngineInputProcessor : public IKeyboardEventListener, public IQuitEventListener {
   private:
   public:
      void keyboardEvent(SDL_KeyboardEvent * keyboardEvent);
      void quitEvent(SDL_QuitEvent * quitEvent);
   };

   GameEngineInputProcessor _gameEngineInputProcessor;
   GameTimer _gameTimer;

public:
   GameEngine();
   ~GameEngine();
   void turnKey(GameWorld * gameWorld);
};

typedef Singleton<GameEngine> GlobalGameEngine;
#define globalGameEngine GlobalGameEngine::instance();

#endif
