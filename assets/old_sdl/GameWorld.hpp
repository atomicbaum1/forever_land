#ifndef __GAME_WORLD_HPP__
#define __GAME_WORLD_HPP__

#include "GameTimer.hpp"
#include "Framerate.hpp"

class GameWorld {
protected:
   GameTimer _gameTimer;
   SDL_Renderer * _pRenderer;
   Uint64 _delta;
   Framerate _framerate;
   const char * _filename;

   virtual void _loadWorldData() = 0;
   virtual void _destroyWorldData() = 0;
   virtual bool _worldLoop() = 0;

public:
   GameWorld();
   virtual ~GameWorld();
   void loadWorld(const char * filename);
   void startWorld();
};

#endif
