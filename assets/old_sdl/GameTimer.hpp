#ifndef __GAME_TIMER_HPP__
#define __GAME_TIMER_HPP__

#include "SDLIncludes.hpp"

enum GameTimerState {
   GameTimerState_Running,
   GameTimerState_Stopped,
   GameTimerState_Paused,
};

class GameTimer {
protected:
   static Uint64 _timer_frequency;

   Uint64 _last, _current, _delta, _uptime;
   GameTimerState _state;

public:
   GameTimer();
   virtual ~GameTimer();
   void start();
   void stop();
   void pause();
   void resume();
   void update();
   Uint64 getDelta();
   Uint64 getUptime();
   GameTimerState getState();
   static Uint64 getTimerFrequency();
};

#endif
