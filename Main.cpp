#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "health/System.hpp"
#include "net/UdpConnection.hpp"
#include <thread>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    // Print the System info
    std::cout << "Version Info:" << std::endl;
    std::cout << System::getSdlVersions() << std::endl;

    // UDP Connection
    auto connection = new AFS::UdpConnection("localhost", 6666);
    connection->open();
    connection->close();

    SDLNet_Quit();
    SDL_Quit();

    return 0;
}