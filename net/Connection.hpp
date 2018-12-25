
///
/// @file Connection.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once
#include <cstdint>
#include <string>
#include <SDL_net.h>

/// @brief Baum Network
namespace BaumNetwork {
    /// @brief Basic connection
    class Connection {
    public:
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void rx(std::string &data, IPaddress *ipAddr) = 0;
        virtual void tx(const std::string &data, IPaddress *ipAddr) = 0;
        virtual bool dataReady() = 0;
    };

}; // Baum Network Namespace

