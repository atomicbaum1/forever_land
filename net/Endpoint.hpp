
///
/// @file Endpoint.hpp
/// @brief Network endpoint definitions
/// @author Matthew Baum
/// @copyright (c) 2018 Arctic Fox Studio, LTD. All rights reserved.
///

#pragma once
#include <functional>

/// @brief Arctic Fox Studio
namespace AFS {

    /// @brief Network endpoint
    class Endpoint {
    private:
        std::vector<std::function> _onConnect{};  /// Called when the endpoint is connected
        std::vector<std::function> _onDisconnect{};  /// Called when an endpoint disconnect is noticed
        std::vector<std::function> _onRx{};  /// Called when data is received
        std::vector<std::function> _onTx{};  /// Called when data is sent
        std::vector<Endpoint> _connections;  /// Currently connected endpoints
    };

}; // Arctic Fox Studio Namespace

