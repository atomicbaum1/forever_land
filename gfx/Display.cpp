
///
/// @file Display.cpp
/// @brief System display functions.  Includes the SDL window and SDL renderer.
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Display.hpp"
#include "InitException.hpp"
#include <string>

/// @brief Baum Network
namespace BaumNetwork {

    Display::Display(const char *title) {
        _title = title;
    }

    Display::~Display() {

        if (_pWindow != NULL) {
            SDL_DestroyWindow(_pWindow);
            _pWindow = NULL;
        }

        if (_pRenderer != NULL) {
            SDL_DestroyRenderer(_pRenderer);
            _pRenderer = NULL;
        }
    }

    void Display::initDisplay(DisplaySettings *pDisplaySettings) {
        memcpy(&_displaySettings, pDisplaySettings, sizeof _displaySettings);

        // TODO: Fix for other settings

        // Init the window
        _pWindow = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    _displaySettings.width, _displaySettings.height, SDL_WINDOW_SHOWN);
        if (_pWindow == NULL) {
            throw initException("Could not init the window", GameExceptionSeverity_Assert);
        }

        // Init the renderer
        _pRenderer = SDL_CreateRenderer(_pWindow, -1, SDL_RENDERER_ACCELERATED);
        if (_pRenderer == NULL) {
            throw initException("Could not init the renderer", GameExceptionSeverity_Assert);
        }

        // Do one render to clear to the default color
        SDL_SetRenderDrawColor(_pRenderer, 255, 0, 255, 255); // Pink/purple-ish... Just a debug color
        SDL_RenderClear(_pRenderer);
        SDL_RenderPresent(_pRenderer);
    }

    SDL_Renderer *Display::getRenderer() const {
        return _pRenderer;
    }

    SDL_Window *Display::getWindow() const {
        return _pWindow;
    }

    void Display::render() const {
        SDL_RenderPresent(_pRenderer);
    }

    void Display::clear() const {
        SDL_RenderClear(_pRenderer);
    }

}