///
/// @file Logging.hpp
/// @brief Logging code for debugging
/// @author Matthew Baum
/// @copyright (c) 2018 Baum Network. All rights reserved.
///


#pragma once

/// When defined, debug logging is enabled
#define DEBUGGING_ON

#ifdef DEBUGGING_ON

#include <iostream>
#define LOG(string) { std::cout << __FILE__ << "::" << __FUNCTION__ << "() : " << __LINE__ << " | "  << (string) \
                      << std::endl; }

#else

#define LOG(string)

#endif