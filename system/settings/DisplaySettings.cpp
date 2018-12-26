///
/// @file DisplaySettings.cpp
/// @brief Settings load/save management for the display
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "DisplaySettings.hpp"
#include <sstream>
#include <map>
#include <cstring>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Logging.hpp"

/// @brief Loads the JSON display settings from a filename
/// @param filename Name of the JSON display settings file to load
/// @return true upon successful loading, false otherwise
bool BaumNetwork::DisplaySettings::loadSettings(std::string filename) {
    namespace pt = boost::property_tree;
    pt::ptree root;

    try {
        pt::read_json(filename, root);

        globalLogger->log(std::string("Loading settings from file ") + filename,
                          BaumNetwork::LogSeverity::DEBUG);

        _data.width = root.get<unsigned int>("DisplaySettings.Width");
        globalLogger->log(std::string("Display Width: ") + std::to_string(_data.width),
                          BaumNetwork::LogSeverity::DEBUG);

        _data.height = root.get<unsigned int>("DisplaySettings.Height");
        globalLogger->log(std::string("Display Height: ") + std::to_string(_data.height),
                          BaumNetwork::LogSeverity::DEBUG);

        _data.windowed = root.get<bool>("DisplaySettings.Windowed");
        globalLogger->log(std::string("Display windowed: ") + std::to_string(_data.windowed),
                          BaumNetwork::LogSeverity::DEBUG);
    } catch (...) {
        globalLogger->log(std::string("Cannot load settings for file " + filename), BaumNetwork::LogSeverity::ERROR);
        return false;
    }

    globalLogger->log(std::string("Done loading settings"), BaumNetwork::LogSeverity::DEBUG);
    return true;
}

/// @brief Gets the display settings if they have been loaded
/// @return Settings that were loaded
const BaumNetwork::DisplaySettingsData & BaumNetwork::DisplaySettings::getSettings() const {
    globalLogger->log(std::string("Getting display data"), BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display Width: ") + std::to_string(_data.width), BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display Height: ") + std::to_string(_data.height), BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display windowed: ") + std::to_string(_data.windowed),
            BaumNetwork::LogSeverity::DEBUG);
    return _data;
}

/// @brief Saves the settings
/// @return true upon successful save, false otherwise
bool BaumNetwork::DisplaySettings::saveSettings(std::string filename, BaumNetwork::DisplaySettingsData & settings) {
    namespace pt = boost::property_tree;

    globalLogger->log(std::string("Saving display data"), BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display Width: ") + std::to_string(settings.width), BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display Height: ") + std::to_string(settings.height),
            BaumNetwork::LogSeverity::DEBUG);
    globalLogger->log(std::string("Display windowed: ") + std::to_string(settings.windowed),
            BaumNetwork::LogSeverity::DEBUG);

    try {
        // Attempt to write
        pt::ptree root;
        root.put("DisplaySettings.Width", settings.width);
        root.put("DisplaySettings.Height", settings.height);
        root.put("DisplaySettings.Windowed", settings.windowed);
        pt::write_json(filename, root);
    } catch(...) {
        // Failure
        globalLogger->log(std::string("Error saving display data"), BaumNetwork::LogSeverity::DEBUG);
        return false;
    }

    // Copy the data over
    _data = settings;

    // Success
    globalLogger->log(std::string("Save data success"), BaumNetwork::LogSeverity::DEBUG);
    return true;
}
