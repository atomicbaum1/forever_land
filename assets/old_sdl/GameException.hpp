#ifndef __GAME_EXCEPTION__
#define __GAME_EXCEPTION__

#include <sstream>

enum GameExceptionSeverity {
   GameExceptionSeverity_Info,
   GameExceptionSeverity_Warning,
   GameExceptionSeverity_Error,
   GameExceptionSeverity_Assert,
};

class GameException {
protected:
   std::string _exceptionMessage;
   GameExceptionSeverity _severity;

   virtual const char * const _getExceptionName() const { return "GameException"; }

public:
   GameException(const char * file, const char * function, int line, const char * message, GameExceptionSeverity severity);
   GameException(const char * file, const char * function, int line, std::string & message, GameExceptionSeverity severity);
   virtual ~GameException();

   virtual void getExceptionString(std::string & string) const;
   virtual GameExceptionSeverity getExceptionSeverity() const;
};

#define gameException(message, severity) GameException(__FILE__, __FUNCTION__, __LINE__, message, severity)

#endif
