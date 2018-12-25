#ifndef __FRAMERATE_HPP__
#define __FRAMERATE_HPP__

#include "SDLIncludes.hpp"
#include "Updatable.hpp"

#define STANDARD_FPS 60
#define TICKS_PER_FRAME(fps) 1000.0 / (double)fps
#define FPS_NO_LIMIT -1

class Framerate : public IUpdatable {
private:
   Uint64 _counter;
   Uint64 _frames;
   double _fps;
   int _fpsLimit;

public:
   Framerate();
   void update(Uint64 delta);
   double getFps() const ;
   void limitFps(int value);
};

#endif
