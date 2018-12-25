#include "SDLIncludes.hpp"
#include "GameTimer.hpp"

Uint64 GameTimer::_timer_frequency = 0;

GameTimer::GameTimer() :
_last(0), _current(0), _delta(0), _uptime(0), _state(GameTimerState_Stopped) {

}

GameTimer::~GameTimer() {

}

void GameTimer::start() {
   _state = GameTimerState_Running;
   _last = _current = SDL_GetPerformanceCounter(); // SDL_GetTicks();
}

void GameTimer::stop() {
   _state = GameTimerState_Stopped;
   _last = _current = _delta = _uptime = 0;
}

void GameTimer::pause() {
   _state = GameTimerState_Paused;
}

void GameTimer::resume() {
   _state = GameTimerState_Running;
   _last = _current = SDL_GetPerformanceCounter(); // SDL_GetTicks();
   _delta = 0;
}

void GameTimer::update() {
   if (_state == GameTimerState_Running) {
      _last = _current;
      _current = SDL_GetPerformanceCounter(); // SDL_GetTicks();
      _delta = _current - _last;
      _uptime += _delta;
   }
}

Uint64 GameTimer::getDelta() {
   return _delta;
}

Uint64 GameTimer::getUptime() {
   return _uptime;
}

GameTimerState GameTimer::getState() {
   return _state;
}

Uint64 GameTimer::getTimerFrequency() {
   static bool haveFrequency = false;
   if (!haveFrequency) {
      haveFrequency = true;
      _timer_frequency = SDL_GetPerformanceFrequency();
   }
   return _timer_frequency;
}
