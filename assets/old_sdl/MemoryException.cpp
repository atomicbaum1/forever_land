#include "MemoryException.hpp"

MemoryException::MemoryException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity) :
   GameException(file, function, line, message, severity) {
   // Empty body
}
MemoryException::MemoryException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity) :
   GameException(file, function, line, message, severity) {
   // Empty body
}

MemoryException::~MemoryException() {
   // Empty body
}
