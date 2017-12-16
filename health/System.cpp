
//
// Created by Matthew Baum on 12/15/17.
// Copyright (c) 2017 Arctic Fox Studio, LTD. All rights reserved.
//

#include <SDL_version.h>
#include <SDL_net.h>
#include <boost/format.hpp>
#include "System.hpp"

std::string System::_sdlVersionString{};

// Get the SDL version strings.
// Currently includes the version strings for:
//   SDL2
//   SDL2_net
const std::string &System::getSdlVersions() {

    if (!_sdlVersionString.empty()) {
        return _sdlVersionString;
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
    const SDL_version * sdlNetLinkedVersion = SDLNet_Linked_Version();
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
