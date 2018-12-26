///
/// @file DisplaySettings.hpp
/// @brief Settings load/save management for the display
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include "Settings.hpp"

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Display settings holding container for easy return
    struct DisplaySettingsData {
        unsigned int width{0};  /// Width of the window
        unsigned int height{0};  /// Height of the window
        bool windowed{true};  /// True if in windowed mode
    };

    /// @brief Settings for the window/display
    class DisplaySettings : public ISettings<DisplaySettingsData> {
    private:
        DisplaySettingsData _data;  /// @brief data settings to return back

    public:
        ~DisplaySettings() override = default;
        bool loadSettings(std::string filename) override;
        const DisplaySettingsData & getSettings() const override;
        bool saveSettings(std::string filename, DisplaySettingsData & settings) override;
    };

}; // Baum Network Namespace

