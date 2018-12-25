#ifndef __RENDERABLE_HPP__
#define __RENDERABLE_HPP__

#include "SDLIncludes.hpp"

class IRenderable {
public:
   virtual void render(SDL_Renderer * pRenderer) = 0;
};

#endif
