
///
/// @file Textures.hpp
/// @brief Texture loading and manipulation functions
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Texture namespace
    namespace Textures {
        SDL_Texture * loadImageFromFile(SDL_Renderer * renderer, std::string imageName);
        std::vector<SDL_Texture *> loadImagesFromAtlas(SDL_Renderer * renderer, std::string imageName,
                unsigned int width, unsigned int height);
        SDL_Texture * getFrameFromSurface(SDL_Renderer * renderer, SDL_Surface * source, unsigned int width,
                unsigned int height, unsigned int position) noexcept;
    }

}; // Baum Network Namespace

