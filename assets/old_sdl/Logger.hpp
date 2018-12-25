#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>
#include <fstream>
#include <iostream>
#include "Singleton.hpp"
#include "DebugDefines.hpp"

#define INFO_LOG_ENTRY  "[INFO ] : "
#define DEBUG_LOG_ENTRY "[DEBUG] : "
#define ERROR_LOG_ENTRY "[ERROR] : "
#define DEFAULT_LOG_NAME "log.txt"
#define MAX_LOG_SIZE 4096

enum LogLevel {
   LogLevel_Info = (1u << 0),
   LogLevel_Debug = (1u << 1),
   LogLevel_Error = (1u << 2),
};

class Logger {
protected:
   const char * _pFileName;
   std::fstream * _pFileStream;
   unsigned int _logLevel;

   void _logAll(const char * message, const char * messageHeader, LogLevel logLevel);
public:
   Logger();
   ~Logger();
   void openLogFile(const char * filename = DEFAULT_LOG_NAME);
   void closeLogFile();
   void setLogLevel(unsigned int logLevel);
   void logInfo(std::string & message);
   void logDebug(std::string & message);
   void logError(std::string & message);
   void logInfo(const char * message);
   void logDebug(const char * message);
   void logError(const char * message);
   bool logIsOpen();
};

typedef Singleton<Logger> GlobalLogger;
#define globalLogger GlobalLogger::instance()

#endif
