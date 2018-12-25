#ifndef __UPDATABLE_HPP__
#define __UPDATABLE_HPP__

#include "SDLIncludes.hpp"

class IUpdatable {
public:
   virtual ~IUpdatable() {}
   virtual void update(Uint64 delta) = 0;
};

#endif
