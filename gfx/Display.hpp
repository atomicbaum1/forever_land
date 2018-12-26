///
/// @file Display.hpp
/// @brief SDL Display operations
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "DisplaySettings.hpp"
#include "Singleton.hpp"

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Window/Display operations
    class Display {
    protected:
        DisplaySettingsData _displaySettings;  /// Display settings data
        SDL_Renderer *_pRenderer;  /// SDL Renderer
        SDL_Window *_pWindow;  /// SDL Window data
        SDL_DisplayMode *_pDisplayMode;  /// SDL Display mode
        std::string _title{"-/-"};

    public:
        explicit Display(const std::string & title, const DisplaySettingsData & displaySettingsData);
        ~Display();
        void initDisplay();
        SDL_Renderer *getRenderer() const;
        SDL_Window *getWindow() const;
        void render() const;
        void clear() const;
    };

    /// @brief Global display to be used in the main thread
    typedef Singleton <Display> GlobalDisplay;
    #define globalDisplay GlobalDisplay::instance()
}
