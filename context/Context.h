//
// Created by mbaum on 5/23/18.
//

#pragma once

#include <string>
#include <fstream>
#include "../system/Logging.h"

namespace AFS {

    /// @brief Options for a context
    struct ContextOptions {
        bool getTicks{false};
        std::string logFile{""};
    };

    int _contextCallback(void * data);

    /// @breif A thread context
    class Context {
    private:
        /// @brief User configurable context options
        ContextOptions _options;
        std::ofstream _logfile;

    public:
        /// @brief Context constructor
        /// @param [in] Context options for specific context settings
        explicit Context(ContextOptions &options);
        /// @brief Default context constructor with default context options
        Context(): _options{ContextOptions()} {}

        /// @brief Closes the logfile
        ~Context();

        /// @brief Pauses the context
        void pause();

        /// @breif Stops the context gracefully
        void stop();

        /// @brief Starts the context
        void run();

        /// @brief Logs
        void log(std::string string);
    };
}