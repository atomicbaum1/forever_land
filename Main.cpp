#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "system/System.hpp"
#include "net/UdpConnection.hpp"
#include <thread>
#include "context/Context.h"

enum class ClientConnectionState {
    Hello,
    Connected
};

class Client : public AFS::Context {
private:
    AFS::UdpConnection * _connection{nullptr};
    ClientConnectionState _state{ClientConnectionState::Hello};

public:

    Client() {
        _connection = new AFS::UdpConnection("localhost", 0);
        _connection->open();
    }
    ~Client() {
        _connection->close();
    }
    void run(AFS::ContextTick & contextTick) override {

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

class Server : public AFS::Context {
private:
    AFS::UdpConnection * _connection{nullptr};
    ClientConnectionState _state{ClientConnectionState::Hello};

public:
    Server() {
        _connection = new AFS::UdpConnection("localhost", 6666);
        _connection->open();
    }
    ~Server() {
        _connection->close();
    }
    void run(AFS::ContextTick & contextTick) override {

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

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    // Print the System info
    std::cout << "Version Info:" << std::endl;
    std::cout << System::getSdlVersions() << std::endl;

    auto client = new Client();
    auto server = new Server();

    client->start("client");
    server->start("server");

    client->wait();
    server->wait();

    SDLNet_Quit();
    SDL_Quit();

    return 0;
}