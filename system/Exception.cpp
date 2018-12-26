
///
/// @file Exception.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Exception.hpp"

/// @brief Baum Network
namespace BaumNetwork {
    Exception::Exception(const std::string & description) : Exception(description, ExceptionSeverity::WARNING) {
    }

    Exception::Exception(const std::string & description, ExceptionSeverity severity) :
            description{description}, severity{severity} {
    }
}
