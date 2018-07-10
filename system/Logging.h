//
// Created by mbaum on 7/9/18.
//

#pragma once

#define DEBUGGING_ON

#ifdef DEBUGGING_ON

#include <iostream>
#define LOG(string) { std::cout << __FILE__ << "::" << __FUNCTION__ << "() : " << __LINE__ << " | "  << (string) \
                      << std::endl; }

#else

#define LOG(string)

#endif