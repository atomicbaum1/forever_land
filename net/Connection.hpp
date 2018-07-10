
///
/// @file Connection.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Arctic Fox Studio, LTD. All rights reserved.
///

#pragma once
#include <cstdint>
#include <string>

/// @brief Arctic Fox Studio
namespace AFS {
    /// @brief Basic connection
    class Connection {
    public:
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void rx(std::string &data) = 0;
        virtual void tx(const std::string &data) = 0;
        virtual bool dataReady() = 0;
    };

}; // Arctic Fox Studio Namespace

