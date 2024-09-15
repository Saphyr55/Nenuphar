#pragma once

#define NSTRING(s) #s

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define NP_PLATFORM_WINDOWS true
#endif

#ifndef NP_PROJECT_DIR
    #pragma #error "The macro 'NP_PROJECT_DIR' is not define."
#endif

#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Core/Debug.hpp"
