#include "GameException.hpp"

GameException::GameException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity) {
   std::stringstream sstream;
   sstream << "Exception \"" << _getExceptionName() << "\" found in " << file << "::" << function << "::" << line << ": " << message << " - severity (" <<
      severity << ")";
   _exceptionMessage = sstream.str();
}

GameException::GameException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity) :
   GameException(file, function, line, message.c_str(), severity) {
   // Empty body
}

GameException::~GameException() {
   // Empty body
}

void GameException::getExceptionString(std::string & string) const {
   string = _exceptionMessage;
}

GameExceptionSeverity GameException::getExceptionSeverity() const {
   return _severity;
}
