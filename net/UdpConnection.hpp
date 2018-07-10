
///
/// @file UdpConnection.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Arctic Fox Studio, LTD. All rights reserved.
///

#pragma once
#include <string>

/// @brief Arctic Fox Studio
#include "Connection.hpp"
#include <SDL_net.h>

namespace AFS {

    /// @brief Basic and raw UDP Connection class to open/close connections.  It also can get and send data
    class UdpConnection : public Connection {
    private:
        UDPsocket _socket;  /// Our rx/tx socket
        std::string _destIpAddress;
        std::uint16_t _destPort;
        UDPpacket * _in, *_out;  /// In and out UDP packets
    public:
        UdpConnection(std::string destIpAddress, std::uint16_t destPort);
        void open() final;
        void close() final;
        void rx(std::string &data) final;
        void tx(const std::string &data) final;
        bool dataReady() final;
    };

}; // Arctic Fox Studio Namespace

