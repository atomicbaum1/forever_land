
///
/// @file UdpConnection.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include <cstdint>
#include "UdpConnection.hpp"
#include <exception>
#include <stdexcept>
#include <SDL_net.h>
#include <iostream>
#include <sstream>

/// @breif Opens a UDP Connection
/// @throw std::runtime_error with message on failure
void BaumNetwork::UdpConnection::open() {
    if (!(this->_socket = SDLNet_UDP_Open(this->_destPort))) { // If we couldn't open the socket
        throw std::runtime_error(std::string("Failed: ") + SDLNet_GetError());
    }
}

/// @brief Closes the connection
void BaumNetwork::UdpConnection::close() {
    SDLNet_UDP_Close(this->_socket);
    this->_socket = nullptr;
}

/// @brief Receive data on the wire
/// @param [out] data RX data
void BaumNetwork::UdpConnection::rx(std::string &data, IPaddress *ipAddr) {
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

/// @brief Transmits data on the wire
/// @param [in] data TX data
void BaumNetwork::UdpConnection::tx(const std::string &data, IPaddress *ipAddr) {
    // Convert the string to the packet data type

    SDLNet_ResizePacket(this->_out, 1024);
    this->_out->data = (Uint8*)new char[data.length()];
    this->_out->len = (Uint16)data.size();
    this->_out->address = *ipAddr;
    if (!SDLNet_UDP_Send(this->_socket, -1, this->_out)) {
        std::cout << "Error sending packet" << std::endl;
    }
}

/// @brief Detects if the data is ready to read on the wire
/// @return true if data is ready, false otherwise
bool BaumNetwork::UdpConnection::dataReady() {
    return (bool)SDLNet_SocketReady(this->_socket);
}

/// @brief Creates a UDP connection based off an IP and port
/// @param [in] destIpAddress Destination IP address
/// @param [in] destPort Destination port number
BaumNetwork::UdpConnection::UdpConnection(std::string destIpAddress, std::uint16_t destPort) {
    this->_destIpAddress = std::move(destIpAddress);
    this->_destPort = destPort;

    if (!(this->_in = SDLNet_AllocPacket(sizeof(std::uint16_t)))) {
        throw std::runtime_error(std::string("Failed: ") + SDLNet_GetError());
    }

    if (!(this->_out = SDLNet_AllocPacket(sizeof(std::uint16_t)))) {
        throw std::runtime_error(std::string("Failed: ") + SDLNet_GetError());
    }
}
