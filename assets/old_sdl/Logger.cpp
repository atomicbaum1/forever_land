#include <cstdarg>
#include <sstream>
#include "Logger.hpp"
#include "InitException.hpp"

#ifdef WINDOWS_COMPILE
#ifdef OUTPUT_TO_CONSOLE

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

static void stdioToWindowsConsole() {
   int consoleHandle;
   long ioHandle;
   CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo;
   FILE *fp;

   AllocConsole();

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo);
   consoleBufferInfo.dwSize.Y = MAX_CONSOLE_LINES;
   SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), consoleBufferInfo.dwSize);

   ioHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
   consoleHandle = _open_osfhandle(ioHandle, _O_TEXT);
   fp = _fdopen(consoleHandle, "w");
   *stdout = *fp;

   setvbuf(stdout, NULL, _IONBF, 0);

   ioHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
   consoleHandle = _open_osfhandle(ioHandle, _O_TEXT);
   fp = _fdopen(consoleHandle, "r");
   *stdin = *fp;

   setvbuf(stdin, NULL, _IONBF, 0);

   ioHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
   consoleHandle = _open_osfhandle(ioHandle, _O_TEXT);
   fp = _fdopen(consoleHandle, "w");
   *stderr = *fp;

   setvbuf(stderr, NULL, _IONBF, 0);

   std::ios::sync_with_stdio();
}

#endif
#endif

void Logger::_logAll(const char * message, const char * messageHeader, LogLevel logLevel) {
   std::stringstream stream;

   stream << messageHeader;

   if ((_pFileStream != NULL) && _pFileStream->is_open() && (_logLevel & logLevel)) {
      stream << message;
      _pFileStream->write(stream.str().c_str(), stream.str().size());
#ifdef OUTPUT_TO_CONSOLE
      std::cout << stream.str() << std::endl;
#endif
   }
}

Logger::Logger() : _pFileName(NULL), _pFileStream(NULL) {
#ifdef WINDOWS_COMPILE
#ifdef OUTPUT_TO_CONSOLE
   stdioToWindowsConsole();
#endif
#endif
}

Logger::~Logger() {
   _pFileName = NULL;

   if (_pFileStream != NULL) {
      if (_pFileStream->is_open()) {
         _pFileStream->close();
      }
      delete _pFileStream;
      _pFileStream = NULL;
   }
}


void Logger::openLogFile(const char * filename) {
   if ((_pFileName == NULL) && (_pFileStream == NULL)) {
      _pFileName = filename;
      _pFileStream = new std::fstream();
      _pFileStream->open(_pFileName, std::ofstream::out | std::ofstream::app);

      if (!_pFileStream->is_open()) {
         throw initException("Could not init the logger", GameExceptionSeverity_Assert);
      }
   }
}

void Logger::closeLogFile() {
   if ((_pFileStream != NULL) && _pFileStream->is_open()) {
      _pFileStream->close();
   }
}

void Logger::setLogLevel(unsigned int logLevel) {
   _logLevel = logLevel;
}

void Logger::logInfo(std::string & message) {
   logInfo(message.c_str());
}

void Logger::logDebug(std::string & message) {
   logDebug(message.c_str());
}

void Logger::logError(std::string & message) {
   logError(message.c_str());
}

void Logger::logInfo(const char * message) {
   _logAll(message, INFO_LOG_ENTRY, LogLevel_Info);
}

void Logger::logDebug(const char * message) {
   _logAll(message, DEBUG_LOG_ENTRY, LogLevel_Debug);
}

void Logger::logError(const char * message) {
   _logAll(message, ERROR_LOG_ENTRY, LogLevel_Error);
}

bool Logger::logIsOpen() {
   if ((_pFileStream == NULL) || _pFileStream->is_open()) {
      return false;
   }
   return true;
}
