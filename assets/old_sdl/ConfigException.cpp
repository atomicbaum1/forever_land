#include "ConfigException.hpp"

ConfigException::ConfigException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity) :
GameException(file, function, line, message, severity) {
   // Empty body
}
ConfigException::ConfigException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity) :
GameException(file, function, line, message, severity) {
   // Empty body
}

ConfigException::~ConfigException() {
   // Empty body
}
