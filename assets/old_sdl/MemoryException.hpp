#ifndef __MEMORY_EXCEPTION__
#define __MEMORY_EXCEPTION__

#include "GameException.hpp"

class MemoryException : public GameException {
protected:
   virtual const char * const _getExceptionName() const { return "MemoryException"; }

public:
   MemoryException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity);
   MemoryException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity);
   virtual ~MemoryException();
};

#define memoryException(message, severity) MemoryException(__FILE__, __FUNCTION__, __LINE__, message, severity)

#endif
