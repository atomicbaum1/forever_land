
///
/// @file Textures.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Textures.hpp"
#include "Exception.hpp"
#include "Logging.hpp"
#include <SDL_image.h>

/// @brief Baum Network namespace
namespace BaumNetwork {

    /// @brief Texture namespace
    namespace Textures {

        /// @brief Create a texture from a filename
        /// @throws Exception when the image cannot be successfully loaded
        /// @param renderer Pointer to the global renderer
        /// @param imageName Name of the texture to load from the filesystem
        /// @return Texture of the image loaded
        SDL_Texture *loadImageFromFile(SDL_Renderer *renderer, std::string imageName) {
            // Load the surface
            SDL_Surface * tempSurface = IMG_Load(imageName.c_str());
            if (!tempSurface) {
                LOG(std::string("Could not load image " + imageName));
                throw Exception(std::string("Could not load image " + imageName));
            }

            // Turn the surface into a texture
            SDL_Texture * retTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

            // Free the temporary surface
            SDL_FreeSurface(tempSurface);

            if (!retTexture) {
                LOG(std::string("Could not create texture from surface " + imageName));
                throw Exception(std::string("Could not create texture from surface " + imageName));
            }

            // Return the texture
            return retTexture;
        }


        /// @brief Create a vector of textures from a filename
        /// @throws Exception when the image cannot be successfully loaded
        /// @param renderer Pointer to the global renderer
        /// @param imageName Name of the texture to load from the filesystem
        /// @param width Width of the individual images to cut from the atlas
        /// @param height Height of the individual images to cut from the atlas
        /// @return Texture of the image loaded
        std::vector<SDL_Texture *> loadImagesFromAtlas(SDL_Renderer *renderer, std::string imageName,
                unsigned int width, unsigned int height) {
            // Load the surface
            SDL_Surface * tempSurface = IMG_Load(imageName.c_str());

            if (!tempSurface) {
                LOG(std::string("Could not load image " + imageName));
                throw Exception(std::string("Could not load image " + imageName));
            }

            // Cut up the surface into multiple textures
            std::vector<SDL_Texture *> retTextures;
            SDL_Texture * tempTexture{nullptr};
            unsigned int position = 0;
            while ((tempTexture = getFrameFromSurface(renderer, tempSurface, width, height, position++)) != nullptr) {
                retTextures.push_back(tempTexture);
            }

            // Free the temporary surface
            SDL_FreeSurface(tempSurface);

            // Return the vector of textures
            return retTextures;
        }

        /// @brief Load a single frame from the surface
        /// @param renderer Pointer to the global renderer
        /// @param source Source surface
        /// @param width Width of the individual images to cut from the atlas
        /// @param height Height of the individual images to cut from the atlas
        /// @param position Position of the next image to extract
        /// @return Texture of the cut image loaded, nullptr when the position is exhausted
        SDL_Texture * getFrameFromSurface(SDL_Renderer * renderer, SDL_Surface * source, unsigned int width,
                                          unsigned int height, unsigned int position) noexcept {
            // TODO: Finish function
            return nullptr;
        }
    }
}