
///
/// @file Textures.hpp
/// @brief Texture loading and manipulation functions
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once
#include <string>

/// @brief Baum Network
namespace BaumNetwork {

    class System : final{
    private:
        static std::string _sdlVersionString;

    public:
        System() = default;
        ~System() = default;
        static const std::string &getSdlVersions();
        void init();
        void shutdown();
    };
}




