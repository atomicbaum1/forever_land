
///
/// @file Sprite.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include <SDL_image.h>
#include <string>
#include <vector>
#include "Logging.hpp"

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Basic image rendering
    class Sprite {
    private:
        SDL_Surface * _surface;
    public:
        void loadImageFromFile(std::string imageName);
    };


}; // Baum Network Namespace

