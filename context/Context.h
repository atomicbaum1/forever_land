//
// Created by mbaum on 5/23/18.
//

#pragma once

#include <string>
#include <fstream>
#include <atomic>
#include <thread>
#include <SDL2/SDL_thread.h>
#include "Logging.hpp"

namespace BaumNetwork {

    /// @brief Options for a context
    struct ContextOptions {
        bool getTicks{false};
        std::string logFile{""};
    };

    struct ContextTick {
        u_int64_t delta;
    };

    int _contextCallback(void * data);

    /// @breif A thread context
    class Context {
    private:
        /// @brief User configurable context options
        ContextOptions _options;
        std::ofstream _logfile;
        SDL_Thread * _thread{nullptr};
        void _run();
        std::atomic<bool> _paused{false};
        std::atomic<bool> _stop{false};

    public:
        explicit Context(ContextOptions &options);
        /// @brief Default context constructor with default context options
        Context(): _options{ContextOptions()} {}
        ~Context();
        void pause();
        void unpause();
        void stop();
        void start(const char * name);
        void wait();
        /// @brief Starts the context
        virtual void run(ContextTick & contextTick) = 0;
        void log(std::string string);

        friend int _contextCallback(void * data);
    };
}