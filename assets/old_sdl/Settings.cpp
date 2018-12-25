#include <string>
#include <tinyxml2.h>
#include "SDLIncludes.hpp"
#include "Settings.hpp"
#include "InitException.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "ConfigException.hpp"

// TODO: Do we care about sanatizing this? Don't use strcmp(), etc.
static bool textToBoolean(const char * value) {
   if (strcmp(value, "true")) {
      return true;
   }
   return false;
}

Settings::Settings() {

}

Settings::~Settings() {
   SDL_Quit();
   IMG_Quit();
}

// TODO: Load settings from a file
void Settings::loadSettings(const char * configFile) {

   if (configFile == NULL) {
      _displaySettings.width = DEFAULT_DISPLAY_WIDTH;
      _displaySettings.height = DEFAULT_DISPLAY_HEIGHT;
      _displaySettings.windowed = DEFAULT_DISPLAY_WINDOWED;
   }
   else {
      // Load from file
      tinyxml2::XMLDocument settingsDocument;
      std::stringstream stream;

      if (settingsDocument.LoadFile(configFile) != tinyxml2::XML_NO_ERROR) {
         std::stringstream stream;
         stream << "Could not parse config file \"" << configFile << "\"";
         throw configException(stream.str(), GameExceptionSeverity_Assert);
      }

      // Grab the version number
      _softwareVersion = settingsDocument.FirstChildElement("Settings")->Attribute("version");
      stream << "Running software version " << _softwareVersion;
      globalLogger->logInfo(stream.str());

      // Get display settings
      _displaySettings.width = atoi(settingsDocument.FirstChildElement("Settings")->FirstChildElement("Display")->Attribute("width"));
      _displaySettings.height = atoi(settingsDocument.FirstChildElement("Settings")->FirstChildElement("Display")->Attribute("height"));
      _displaySettings.windowed = textToBoolean(settingsDocument.FirstChildElement("Settings")->FirstChildElement("Display")->Attribute("windowed"));

      // Range check the values
      if (_displaySettings.width < MINIMUM_DISPLAY_WIDTH) {
         _displaySettings.width = MINIMUM_DISPLAY_WIDTH;
      }

      if (_displaySettings.height < MINIMUM_DISPLAY_HEIGHT) {
         _displaySettings.height = MINIMUM_DISPLAY_HEIGHT;
      }

      // Get the world manifest name
      _worldManifestName = settingsDocument.FirstChildElement("Settings")->FirstChildElement("GameWorldManifest")->GetText();

      // Get the starting world name
      _startingWorld = settingsDocument.FirstChildElement("Settings")->FirstChildElement("StartingWorld")->GetText();
      globalLogger->logInfo(_startingWorld);
   }
}

// TODO: Apply settings that we loaded from the file
void Settings::applyLoadSettings() {
   int imageFlags = IMG_INIT_PNG;
   int imageInitValue;

   if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      throw initException(SDL_GetError(), GameExceptionSeverity_Assert);
   }

   imageInitValue = IMG_Init(imageFlags);
   if ((imageInitValue & imageFlags) != imageFlags) {
      throw initException(IMG_GetError(), GameExceptionSeverity_Assert);
   }

   globalDisplay->initDisplay(&_displaySettings);
}

void Settings::getDisplaySettings(DisplaySettings * pDisplaySettings) const {
   memcpy(pDisplaySettings, &_displaySettings, sizeof _displaySettings);
}

void Settings::getAudioSettings(AudioSettings * pAudioSettings) const {
   memcpy(pAudioSettings, &_audioSettings, sizeof _audioSettings);
}

void Settings::getInputSettings(InputSettings * pInputSettings) const {
   memcpy(pInputSettings, &_inputSettings, sizeof _inputSettings);
}

const char * Settings::getWorldManifestName() const {
   return _worldManifestName.c_str();
}

const char * Settings::getSoftwareVersion() const {
   return _softwareVersion.c_str();
}

const char * Settings::getStartingWorld() const {
   return _startingWorld.c_str();
}
