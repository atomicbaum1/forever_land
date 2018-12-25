#ifndef __INPUT_PROCESSOR_HPP__
#define __INPUT_PROCESSOR_HPP__

#include <vector>
#include "SDLIncludes.hpp"
#include "Singleton.hpp"

class IKeyboardEventListener {
public:
   virtual void keyboardEvent(SDL_KeyboardEvent * keyboardEvent) = 0;
};

class IQuitEventListener {
public:
   virtual void quitEvent(SDL_QuitEvent * quitEvent) = 0;
};

class InputProcessor {
private:
   std::vector<IKeyboardEventListener *> _keyboardListeners;
   std::vector<IQuitEventListener *> _quitListeners;

   void _emitKeyboardEvent(SDL_KeyboardEvent * event);
   void _emitQuitEvent(SDL_QuitEvent * event);

public:
   InputProcessor();
   ~InputProcessor();

   void processEvents();
   void registerForKeyboardEvent(IKeyboardEventListener * listener);
   void registerForQuitEvent(IQuitEventListener * listener);
};

typedef Singleton<InputProcessor> GlobalInputProcessor;
#define globalInputProcessor GlobalInputProcessor::instance()

#endif
