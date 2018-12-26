
///
/// @file Logging.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Logging.hpp"
#include "Exception.hpp"
#include <string>
#include <chrono>

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Logs namespace
    namespace Logs {
        const char * DefaultLogFile = "logs.txt";
        const char * InfoLog =    "[INFO]    : ";
        const char * DebugLog =   "[DEBUG]   : ";
        const char * WarningLog = "[WARNING] : ";
        const char * ErrorLog =   "[ERROR]   : ";
    }

    /// @brief Sets the filename
    Logger::Logger(const std::string & filename) : _fileName{filename} {

    }

    /// @brief Attempts to close and clean up the log file
    Logger::~Logger() {
        closeLog();
    }

    /// @brief Opens the log file
    /// @throws Exception WARNING if the log file is already open
    /// @throws Exception FATAL if the log file could not be opened
    void Logger::openLog() {
        _output = new std::ofstream();
        if (_output->is_open()) {
            std::string output = std::string("Output file ") + _fileName + " is already open";
            LOG(output);
            throw Exception(output, ExceptionSeverity::WARNING);
        }
        _output->open(_fileName, std::ofstream::out | std::ofstream::app);

        if (!_output->is_open()) {
            throw Exception("Could not init the logger " + _fileName, ExceptionSeverity::FATAL);
        }
    }

    /// @brief Closes and cleans up the log file
    void Logger::closeLog() {
        if (_output) {
            if (_output->is_open()) {
                _output->close();
            }
            delete _output;
            _output = nullptr;
        }
    }

    /// @breif Attempts to log the string to a file
    /// @param string String to log
    /// @param logSeveity Severity to log (prefix)
    void Logger::log(std::string string, LogSeverity logSeverity) {
        if (!_output->is_open()) {
            LOG("Log file is not open");
            return;
        }

#ifndef DEBUGGING_ON
        // Don't log debug info when debugging is turned off
        if (logSeverity == Logs::DebugLog) {
            return;
        }
#endif

        const char * logPrefix{nullptr};
        switch (logSeverity) {
            case LogSeverity::INFO: logPrefix = Logs::InfoLog; break;
            case LogSeverity::WARNING : logPrefix = Logs::WarningLog; break;
            case LogSeverity::DEBUG: logPrefix = Logs::DebugLog; break;
            case LogSeverity::ERROR: logPrefix = Logs::ErrorLog; break;
            default: logPrefix = Logs::ErrorLog;
        }
        auto time_point = std::chrono::system_clock::now();
        std::time_t now = std::chrono::system_clock::to_time_t(time_point);
        *_output << logPrefix << now << " : " << string << std::endl;
    }
}