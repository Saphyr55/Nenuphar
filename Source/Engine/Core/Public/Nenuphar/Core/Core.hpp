#pragma once

#define NSTRING(s) #s

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define NP_PLATFORM_WINDOWS true
#endif

#ifndef NP_PROJECT_DIR
    #pragma #error "The macro 'NP_PROJECT_DIR' is not define."
#endif


#ifdef NSHARED
    // Exports
    #ifdef _MSC_VER
        #define NAPI __declspec(dllexport)
    #else
        #define NAPI __attribute__((visibility("default")))
    #endif
#else

    // Imports
    #ifdef _MSC_VER
        #define NAPI __declspec(dllimport)
    #else
        #define NAPI
    #endif
#endif

#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Core/Debug.hpp"
