#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "system/System.hpp"
#include "net/UdpConnection.hpp"
#include <thread>
#include "context/Context.h"
#include <SDL_image.h>
#include "Textures.hpp"

#if 0
enum class ClientConnectionState {
    Hello,
    Connected
};

class Client : public BaumNetwork::Context {
private:
    BaumNetwork::UdpConnection * _connection{nullptr};
    ClientConnectionState _state{ClientConnectionState::Hello};

public:

    Client() {
        _connection = new BaumNetwork::UdpConnection("localhost", 0);
        _connection->open();
    }
    ~Client() {
        _connection->close();
    }
    void run(BaumNetwork::ContextTick & contextTick) override {

        if (_state == ClientConnectionState::Hello) {
            LOG("Sending hello")
            IPaddress server;
            SDLNet_ResolveHost(&server, "localhost", 6666);
            _connection->tx("HELLO", &server);
        }

        if (_connection->dataReady()) {
            LOG("Got data")
            _state = ClientConnectionState::Connected;
            std::string data;
            IPaddress server;
            _connection->rx(data, &server);
            std::cout << "Got data: " << data << std::endl;
        }

        if (_state == ClientConnectionState::Connected) {
            LOG("Stopping")
            stop();
        }
    }
};

class Server : public BaumNetwork::Context {
private:
    BaumNetwork::UdpConnection * _connection{nullptr};
    ClientConnectionState _state{ClientConnectionState::Hello};

public:
    Server() {
        _connection = new BaumNetwork::UdpConnection("localhost", 6666);
        _connection->open();
    }
    ~Server() {
        _connection->close();
    }
    void run(BaumNetwork::ContextTick & contextTick) override {

        if (_connection->dataReady()) {
            LOG("Got data")
            IPaddress client;
            std::string data;
            _connection->rx(data, &client);
            _connection->tx("MEOW", &client);
        }

        if (_state == ClientConnectionState::Connected) {
            LOG("Stopping")
            stop();
        }
    }
};
#endif

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        LOG("Could not init SDL_Image");
        return -1;
    }

    // Print the System info
    std::cout << "Version Info:" << std::endl;
    std::cout << BaumNetwork::System::getSdlVersions() << std::endl;

    SDL_Window * sdlWindow{nullptr};
    SDL_Renderer * renderer{nullptr};

    //Create window
    if (!(sdlWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
            SDL_WINDOW_SHOWN))) {
        LOG("Error creating window");
        return -1;
    }
    if (!(renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED))) {
        LOG("Error creating renderer");
    }
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x44, 0xFF, 0xFF );


#if 0
    auto client = new Client();
    auto server = new Server();

    client->start("client");
    server->start("server");

    client->wait();
    server->wait();
#endif

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

    SDLNet_Quit();
    SDL_Quit();

    return 0;
}