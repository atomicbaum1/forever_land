//
// Created by mbaum on 5/23/18.
//

#include "Context.h"
#include <SDL2/SDL.h>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace BaumNetwork {

     /// @brief Pauses the context
    void Context::pause() {
        LOG("Enter")
        _paused = true;
    }

    /// @brief Resume the context
    void Context::unpause() {
        LOG("Enter")
        _paused = false;
    }

    /// @breif Stops the context gracefully
    void Context::stop() {
        LOG("Enter")
        _stop = true;
    }

    /// @brief Wrapper for context->run() instance
    /// @param [in] data Context instance
    int _contextCallback(void * data) {
        if (!data) {
            throw std::runtime_error(std::string("Context callback data is nullptr"));
        }
        auto context = static_cast<Context *>(data);
        context->_run();
        return 0;
    }

    void Context::start(const char * name) {
        LOG("Enter")
        _thread = SDL_CreateThread(_contextCallback, name, this);
        LOG("Done")
    }

    /// @brief Logs to a file and stdout if enabled and log to the logfile if used
    void Context::log(std::string string) {
        LOG(string)
        std::cout << string;
    }

    /// @brief Closes the logfile
    Context::~Context() {
        LOG("Enter")
        _logfile.close();
        LOG("Done")
    }

    /// @brief Context constructor
    /// @param [in] Context options for specific context settings
    Context::Context(ContextOptions &options)  {
        LOG("Enter")
        if (options.logFile.length() != 0) {
            LOG(std::string("Opening logfile ") + options.logFile)
            _logfile.open(options.logFile);
            LOG("Opened")
        }
        LOG("Done")
    }

    void Context::_run() {
        LOG("Enter")
        ContextTick tickInfo;
        // Loop while we are not stopped
        while (!_stop) {

            // If we are paused, just continue
            if (_paused) {
                LOG("Paused")
                continue;
            }

            // Run the loop once
            run(tickInfo);
        }
        LOG("Stopped")
    }

    /// @brief Wait for the thread to finish
    void Context::wait() {
        SDL_WaitThread(_thread, nullptr);
    }
}

