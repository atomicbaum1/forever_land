///
/// @file Display.cpp
/// @brief System display functions.  Includes the SDL window and SDL renderer.
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Display.hpp"
#include "Exception.hpp"
#include "Logging.hpp"

/// @brief Baum Network
namespace BaumNetwork {

    /// @brief Set the display title and the display settings
    /// @param title Title to display on the window bar
    /// @param displaySettingsData General display settings loaded from DisplaySettings
    Display::Display(const std::string & title, const DisplaySettingsData & displaySettingsData) : _title(title),
        _displaySettings(displaySettingsData) {

    }

    /// @brief Cleans up the window and the renderer
    Display::~Display() {
        globalLogger->log(std::string("Cleaning up the display"), BaumNetwork::LogSeverity::DEBUG);
        if (_pWindow != nullptr) {
            globalLogger->log(std::string("Window destroyed"), BaumNetwork::LogSeverity::DEBUG);
            SDL_DestroyWindow(_pWindow);
            _pWindow = nullptr;
        }

        if (_pRenderer != nullptr) {
            globalLogger->log(std::string("Renderer destroyed"), BaumNetwork::LogSeverity::DEBUG);
            SDL_DestroyRenderer(_pRenderer);
            _pRenderer = nullptr;
        }
        globalLogger->log(std::string("Done cleaning up the display"), BaumNetwork::LogSeverity::DEBUG);
    }

    /// @brief Initializes the display and renderer
    /// @throws Exception if a window or renderer could not be created
    void Display::initDisplay() {
        globalLogger->log(std::string("Initializing the display"), BaumNetwork::LogSeverity::DEBUG);
        // Init the window
        if (!(_pWindow = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    _displaySettings.width, _displaySettings.height,
                                    (_displaySettings.windowed ? SDL_WINDOW_SHOWN : SDL_WINDOW_FULLSCREEN)))) {
            globalLogger->log(std::string("Could not init the window"), BaumNetwork::LogSeverity::ERROR);
            throw Exception("Could not init the window", ExceptionSeverity::FATAL);
        }

        // Init the renderer
        if (!(_pRenderer = SDL_CreateRenderer(_pWindow, -1, SDL_RENDERER_ACCELERATED))) {
            globalLogger->log(std::string("Could not init the renderer"), BaumNetwork::LogSeverity::ERROR);
            throw Exception("Could not init the renderer", ExceptionSeverity::FATAL);
        }

        // Do one render to clear to the default color
        SDL_SetRenderDrawColor(_pRenderer, 255, 0, 255, 255); // Pink/purple-ish... Just a debug color
        SDL_RenderClear(_pRenderer);
        SDL_RenderPresent(_pRenderer);
        globalLogger->log(std::string("Display initialized"), BaumNetwork::LogSeverity::DEBUG);
    }

    /// @brief Gets the renderer after the display has been initialized
    /// @return Pointer to the renderer
    SDL_Renderer *Display::getRenderer() const {
        return _pRenderer;
    }

    /// @brief Gets the window after the display has been initialized
    /// @return Pointer to the window
    SDL_Window *Display::getWindow() const {
        return _pWindow;
    }

    /// @brief Renders to the screen
    void Display::render() const {
        SDL_RenderPresent(_pRenderer);
    }

    /// @brief Clears the screen
    void Display::clear() const {
        SDL_RenderClear(_pRenderer);
    }

}