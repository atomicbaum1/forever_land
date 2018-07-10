//
// Created by mbaum on 5/23/18.
//

#include "Context.h"
#include <SDL2>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace AFS {

    /// @brief Wrapper for context->run() instance
    /// @param [in] data Context instance
    int _contextCallback(void * data) {
        LOG("Enter")
        
        if (!data) {
            LOG("Context callback data is nullptr")
            throw std::runtime_error(std::string("Context callback data is nullptr"));
        }
        auto context = static_cast<Context *>(data);
        context->run();
        LOG("Done")
        return 0;
    }

    void Context::pause() {
        LOG("Enter")
    }

    void Context::stop() {
        LOG("Enter")
    }

    void Context::run() {
        LOG("Enter")
    }

    void Context::log(std::string string) {
        LOG(string)
        std::cout << string;
    }

    Context::~Context() {
        LOG("Enter")
        _logfile.close();
        LOG("Done")
    }

    Context::Context(ContextOptions &options)  {
        LOG("Enter")
        if (options.logFile.length() != 0) {
            LOG(std::string("Opening logfile ") + options.logFile)
            _logfile.open(options.logFile);
            LOG("Opened")
        }
        LOG("Done")
    }
}

