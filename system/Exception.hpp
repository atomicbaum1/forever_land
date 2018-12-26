
///
/// @file Exception.hpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#pragma once

#include <string>

/// @brief Baum Network
namespace BaumNetwork {

    enum class ExceptionSeverity {
        MESSAGE,
        WARNING,
        DEBUG,
        FATAL
    };

    /// @brief Basic exception class to hold a message and severity
    struct Exception {
        explicit Exception(const std::string & description);
        explicit Exception(const std::string & description, ExceptionSeverity severity);
        std::string description;  /// Description of the error
        ExceptionSeverity severity;  /// Severity of the error
    };

}; // Baum Network Namespace

