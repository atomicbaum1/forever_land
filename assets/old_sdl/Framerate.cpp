#include "Framerate.hpp"
#include "GameTimer.hpp"

Framerate::Framerate() :
   _counter(0), _frames(0), _fps(0), _fpsLimit(FPS_NO_LIMIT) {

}

void Framerate::update(Uint64 delta) {
   _counter += delta;
   _frames++;

   if (_counter > GameTimer::getTimerFrequency()) {
      _fps = _frames / (_counter / (double)(GameTimer::getTimerFrequency()));
      _counter = 0;
      _frames = 0;
   }

   if (_fpsLimit != FPS_NO_LIMIT) {
      if (delta > TICKS_PER_FRAME(_fpsLimit)) {
         SDL_Delay(1000.0 / (double)(_fpsLimit));
      }
   }
}

double Framerate::getFps() const {
   return _fps;
}

void Framerate::limitFps(int value) {
   _fpsLimit = value;
}
