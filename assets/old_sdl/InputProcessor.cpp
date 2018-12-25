#include "InputProcessor.hpp"

void InputProcessor::_emitKeyboardEvent(SDL_KeyboardEvent * event) {
   std::vector<IKeyboardEventListener *>::iterator itr;
   for (itr = _keyboardListeners.begin(); itr != _keyboardListeners.end(); itr++) {
      (*itr)->keyboardEvent(event);
   }
}

void InputProcessor::_emitQuitEvent(SDL_QuitEvent * event) {
   std::vector<IQuitEventListener *>::iterator itr;
   for (itr = _quitListeners.begin(); itr != _quitListeners.end(); itr++) {
      (*itr)->quitEvent(event);
   }
}

InputProcessor::InputProcessor() {
   // Nothing
}

InputProcessor::~InputProcessor() {
   // Nothing
}

void InputProcessor::processEvents() {
   SDL_Event event;

   if (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
         _emitKeyboardEvent((SDL_KeyboardEvent *)&event);
         break;

      case SDL_QUIT:
         _emitQuitEvent((SDL_QuitEvent *)&event);
         break;

      default:
         break;
      }
   }
}

void InputProcessor::registerForKeyboardEvent(IKeyboardEventListener * listener) {
   _keyboardListeners.push_back(listener);
}

void InputProcessor::registerForQuitEvent(IQuitEventListener * listener) {
   _quitListeners.push_back(listener);
}
