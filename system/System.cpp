
///
/// @file System.cpp
/// @brief System and library information
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include <SDL_version.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <boost/format.hpp>
#include "System.hpp"
#include "Logging.hpp"
#include "Exception.hpp"

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief SDL Version string
    std::string System::_sdlVersionString;

    /// @brief Get the SDL version strings.
    /// @brief Currently includes the version strings for: SDL2, SDL2_net
    /// @return String containing the SDL library versions
    const std::string & System::getSdlVersions() {

        if (!System::_sdlVersionString.empty()) {
            return System::_sdlVersionString;
        }

        boost::format formatter("SDL2:\n"
                                "  Compiled version: %u.%u.%u\n"
                                "  Running version %u.%u.%u\n"
                                "SDL2_net:\n"
                                "  Compiled version: %u.%u.%u\n"
                                "  Running version %u.%u.%u\n");

        // Populate SDL version info
        SDL_version sdlCompiledVersion{};
        SDL_version sdlLinkedVersion{};

        SDL_VERSION(&sdlCompiledVersion);
        SDL_GetVersion(&sdlLinkedVersion);
        formatter % static_cast<uint32_t>(sdlCompiledVersion.major)
        % static_cast<uint32_t>(sdlCompiledVersion.minor)
        % static_cast<uint32_t>(sdlCompiledVersion.patch);

        formatter % static_cast<uint32_t>(sdlLinkedVersion.major)
        % static_cast<uint32_t>(sdlLinkedVersion.minor)
        % static_cast<uint32_t>(sdlLinkedVersion.patch);

        // Populate SDL_net version info
        SDL_version sdlNetCompiledVersion{};
        const SDL_version *sdlNetLinkedVersion = SDLNet_Linked_Version();
        SDL_NET_VERSION(&sdlNetCompiledVersion);
        formatter % static_cast<uint32_t>(sdlNetCompiledVersion.major)
        % static_cast<uint32_t>(sdlNetCompiledVersion.minor)
        % static_cast<uint32_t>(sdlNetCompiledVersion.patch);

        formatter % static_cast<uint32_t>(sdlNetLinkedVersion->major)
        % static_cast<uint32_t>(sdlNetLinkedVersion->minor)
        % static_cast<uint32_t>(sdlNetLinkedVersion->patch);

        _sdlVersionString = formatter.str();
        return _sdlVersionString;
    }

    /// @brief Initialize the SDL subsystem and the game subsystem for globals
    /// @throws Exception when something cannot be initialized
    void System::init() {
        globalLogger->openLog();
        globalLogger->log("System init", LogSeverity::DEBUG);

        std::string errorMessage;

        // Init SDL
        globalLogger->log("Initializing SDL", LogSeverity::DEBUG);
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            errorMessage = std::string("Could not init SDL: ") + SDL_GetError();
            globalLogger->log(errorMessage, LogSeverity::ERROR);
            throw Exception(errorMessage, ExceptionSeverity::FATAL);
        }

        // Init SDL net
        globalLogger->log("Initializing SDL net", LogSeverity::DEBUG);
        if (SDLNet_Init() == -1) {
            errorMessage = std::string("Could not init SDL Net: ") + SDLNet_GetError();
            globalLogger->log(errorMessage, LogSeverity::ERROR);
            throw Exception(errorMessage, ExceptionSeverity::FATAL);
        }

        // Init SDL image
        globalLogger->log("Initializing SDL image", LogSeverity::DEBUG);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            errorMessage = std::string("Could not init SDL Image: ") + SDLNet_GetError();
            globalLogger->log(errorMessage, LogSeverity::ERROR);
            throw Exception(errorMessage, ExceptionSeverity::FATAL);
        }

        globalLogger->log("Init finished.", LogSeverity::DEBUG);
    }

    /// @brief Shutdown the SDL subsystems
    void System::shutdown() {
        globalLogger->log("Shutting down", LogSeverity::DEBUG);
        IMG_Quit();
        SDLNet_Quit();
        SDL_Quit();
        globalLogger->log("Shut down finished.  Goodbye.", LogSeverity::DEBUG);
        globalLogger->closeLog();
    }

}