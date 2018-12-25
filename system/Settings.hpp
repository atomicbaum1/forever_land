
///
/// @file Sprite.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include "Singleton.hpp"
#include <boost/property_tree/json_parser.hpp>


/// @brief Baum Network
namespace BaumNetwork {


#define MINIMUM_DISPLAY_WIDTH 640
#define MINIMUM_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_WIDTH 1280
#define DEFAULT_DISPLAY_HEIGHT 720
#define DEFAULT_DISPLAY_WINDOWED true
#define DEFAULT_SETTINGS_NAME "Settings.xml"

    struct DisplaySettings {
        unsigned int width, height;
        bool windowed;
    };

    struct AudioSettings {
        // TODO: Fill
    };

    struct InputSettings {
        // TODO: Fill
    };

    class Settings {
    protected:
        DisplaySettings _displaySettings;
        AudioSettings _audioSettings;
        InputSettings _inputSettings;
        std::string _worldManifestName;
        std::string _softwareVersion;
        std::string _startingWorld;

    public:
        Settings();

        ~Settings();

        void loadSettings(const char *configFile);

        void applyLoadSettings();

        void getDisplaySettings(DisplaySettings *pDisplaySettings) const;

        void getAudioSettings(AudioSettings *pAudioSettings) const;

        void getInputSettings(InputSettings *pInputSettings) const;

        const char *getWorldManifestName() const;

        const char *getSoftwareVersion() const;

        const char *getStartingWorld() const;
    };

    typedef Singleton<Settings> GlobalSettings;
#define globalSettings GlobalSettings::instance()

}