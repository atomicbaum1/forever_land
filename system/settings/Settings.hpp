
///
/// @file Settings.hpp
/// @brief Settings
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include "Singleton.hpp"
#include <string>

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Settings interface to load and retrieve settings
    template <typename T>
    class ISettings {
    public:
        /// @brief Destructor
        virtual ~ISettings() = default;

        /// @brief Loads the JSON settings from a filename
        /// @param filename Name of the JSON file to load
        /// @return true upon successful loading, false otherwise
        virtual bool loadSettings(std::string filename) = 0;

        /// @brief Gets the settings if they have been loaded
        /// @return Settings that were loaded
        virtual const T & getSettings() const = 0;

        /// @brief Saves the settings
        /// @return true upon successful save, false otherwise
        virtual bool saveSettings(std::string filename, T & settings) = 0;
    };
}
