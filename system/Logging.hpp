///
/// @file Logging.hpp
/// @brief Logging code for debugging
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///


#pragma once

#include <iostream>
#include <fstream>
#include "Singleton.hpp"

/// When defined, debug logging is enabled
#define DEBUGGING_ON

#ifdef DEBUGGING_ON
#define LOG(string) { std::cout << __FILE__ << "::" << __FUNCTION__ << "() : " << __LINE__ << " | "  << (string) \
                      << std::endl; }
#else
#define LOG(string)  /* Compiled out */
#endif

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Logs namespace
    namespace Logs {
        extern const char * DefaultLogFile;
        extern const char * InfoLog;
        extern const char * DebugLog;
        extern const char * WarningLog;
        extern const char * ErrorLog;
    }

    /// @brief Severity of the logs
    enum class LogSeverity {
        INFO,
        DEBUG,
        WARNING,
        ERROR
    };

    /// @brief Logging class that opens a file and logs to it
    class Logger {
    private:
        std::ofstream * _output;
        std::string _fileName;
    public:
        explicit Logger(const std::string & filename = Logs::DefaultLogFile);
        ~Logger();
        void openLog();
        void closeLog();
        void log(std::string string, LogSeverity logSeverity = LogSeverity::INFO);
    };

    typedef Singleton<Logger> GlobalLogger;
    #define globalLogger BaumNetwork::GlobalLogger::instance()
}
