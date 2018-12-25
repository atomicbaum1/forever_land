
///
/// @file Exception.cpp
/// @brief TODO: Add file description
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///

#include "Exception.hpp"
/// @brief Baum Network

namespace BaumNetwork {
    Exception::Exception(std::string description) : Exception(description, ExceptionSeverity::WARNING) {
    }

    Exception::Exception(std::string description, ExceptionSeverity severity) :
            description{std::move(description)}, severity{severity} {
    }
}
