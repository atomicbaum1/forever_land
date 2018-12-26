#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL_image.h>
#include <thread>
#include <string>
#include "System.hpp"
#include "Textures.hpp"
#include "Logging.hpp"
#include "DisplaySettings.hpp"
#include "Display.hpp"

/// @brief entry point
/// @return 0 upon success, other status on failure
int main() {

    // Initialize the SDL and logging subsystems
    auto system = BaumNetwork::System();
    system.init();

    globalLogger->log(std::string("Version info:\n" + BaumNetwork::System::getSdlVersions()),
            BaumNetwork::LogSeverity::DEBUG);

    // Load the settings
    BaumNetwork::DisplaySettings ds;
    if (!ds.loadSettings("/home/mbaum/forever_land/assets/DisplaySettings.json")) {
        globalLogger->log(std::string("Could not load display settings"),
                          BaumNetwork::LogSeverity::ERROR);
        return -1;
    }

    // Create the display
    auto display = new BaumNetwork::Display(std::string("Demo"), ds.getSettings());
    display->initDisplay();
    auto renderer = display->getRenderer();

    globalLogger->log(std::string("Done with subsystem setup"), BaumNetwork::LogSeverity::DEBUG);

    /////////////////////////
    /// Debug code starts ///
    /////////////////////////
    // Load test image
    SDL_Texture * texture = BaumNetwork::Textures::loadImageFromFile(renderer,
            "/home/mbaum/forever_land/assets/image.png");

    //Event handler
    SDL_Event e;
    //While application is running
    bool quit{false};
    while( !quit ) {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
        }
        //Clear screen
        SDL_RenderClear(renderer);
        //Render texture to screen
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        //Update screen
        SDL_RenderPresent(renderer);
    }

    /////////////////////////
    /// Debug code ends ///
    /////////////////////////

    delete display;
    system.shutdown();

    return 0;
}