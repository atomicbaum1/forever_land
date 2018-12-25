#ifndef __CONFIG_EXCEPTION_HPP__
#define __CONFIG_EXCEPTION_HPP__

#include "GameException.hpp"

class ConfigException : public GameException {
protected:
   virtual const char * const _getExceptionName() const { return "ConifgException"; }

public:
   ConfigException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity);
   ConfigException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity);
   virtual ~ConfigException();
};

#define configException(message, severity) InitException(__FILE__, __FUNCTION__, __LINE__, message, severity)

#endif
