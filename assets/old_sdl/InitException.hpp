#ifndef __INIT_EXCEPTION_HPP__
#define __INIT_EXCEPTION_HPP__

#include "GameException.hpp"

class InitException : public GameException {
protected:
   virtual const char * const _getExceptionName() const { return "InitException"; }

public:
   InitException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity);
   InitException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity);
   virtual ~InitException();
};

#define initException(message, severity) InitException(__FILE__, __FUNCTION__, __LINE__, message, severity)

#endif
