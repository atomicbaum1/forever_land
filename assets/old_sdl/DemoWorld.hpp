#ifndef __DEMO_WORLD_HPP__
#define __DEMO_WORLD_HPP__

#include "GameWorld.hpp"
#include "InputProcessor.hpp"
#include "Texture.hpp"

class DemoWorld : public GameWorld, public IKeyboardEventListener {
private:
   Texture * _pBackgroundTexture;

protected:
   virtual void _loadWorldData();
   virtual void _destroyWorldData();
   virtual bool _worldLoop();

public:
   DemoWorld() : GameWorld() {};
   virtual ~DemoWorld() {};
   void keyboardEvent(SDL_KeyboardEvent * keyboardEvent);
};

#endif
