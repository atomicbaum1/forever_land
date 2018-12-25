///
/// @file Sprite.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "Settings.hpp"
#include "Singleton.hpp"

/// @brief Baum Network
namespace BaumNetwork {
    const char * DEFAULT_DISPLAY_TITLE = "TEST TITLE"

    class Display {
    protected:
        DisplaySettings _displaySettings;
        SDL_Renderer *_pRenderer;
        SDL_Window *_pWindow;
        SDL_DisplayMode *_pDisplayMode;
        std::string _title;

    public:
        Display(const char *title = DEFAULT_DISPLAY_TITLE);
        virtual ~Display();
        virtual void initDisplay(DisplaySettings *pDisplaySettings);
        SDL_Renderer *getRenderer() const;
        SDL_Window *getWindow() const;
        void render() const;
        void clear() const;
    };

    /// @brief Global display to be used in the main thread
    typedef Singleton <Display> GlobalDisplay;
    #define globalDisplay GlobalDisplay::instance()
}
