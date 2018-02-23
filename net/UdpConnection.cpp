
///
/// @file UdpConnection.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Arctic Fox Studio, LTD. All rights reserved.
///

#include <cstdint>
#include "UdpConnection.hpp"
#include <exception>
#include <stdexcept>
#include <SDL_net.h>
#include <iostream>
#include <sstream>

UDPsocket AFS::UdpConnection::open() {
    if (!(this->_socket = SDLNet_UDP_Open(this->_destPort))) { // If we couldn't open the socket
        throw std::runtime_error(std::string("Failed: ") + SDLNet_GetError());
    }
}

void AFS::UdpConnection::close() {
    SDLNet_UDP_Close(this->_socket);
    this->_socket = nullptr;
}

void AFS::UdpConnection::rx(std::string &data) {
    // If there is no error (Status != -1) then copy the data to the string
    if (SDLNet_UDP_Recv(this->_socket, this->_in) != -1) {
        // Loop through the packet data to convert it from Uint8 to char to std::string
        std::ostringstream packetData;
        for (int i = 0; i < this->_in->len; ++i) {
            packetData << static_cast<char>(this->_in->data[i]);
        }
        data = packetData.str();
    }
}

void AFS::UdpConnection::tx(const std::string &data) {
    // Convert the string to the packet data type
    memcpy(this->_out->data, data.c_str(), data.length());
    if (!SDLNet_UDP_Send(this->_socket, -1, this->_out)) {
        std::cout << "Error sending packet" << std::endl;
    }
}

bool AFS::UdpConnection::dataReady() {
    return false;
}

AFS::UdpConnection::UdpConnection(std::string destIpAddress, std::uint16_t destPort) {
    this->_destIpAddress = destIpAddress;
    this->_destPort = destPort;

    if (!(this->_in = SDLNet_AllocPacket(sizeof(std::uint16_t)))) {
        throw std::runtime_error(std::string("Failed: ") + SDLNet_GetError());
    }
}
