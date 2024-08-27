#pragma once

#include <cassert>

#define NP_ASSERT(exp) assert(exp)

#if defined(_MSC_VER)
    #define NP_DEBUG_BREAK __debugbreak()
#else
    #define NP_DEBUG_BREAK
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define CHECK(exp)     \
    if (!(exp))          \
    {                  \
        NP_DEBUG_BREAK;\
    }
#else
    #define CHECK(exp)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define DCHECK(exp)     \
    if constexpr (!(exp)) \
    {                   \
        NP_DEBUG_BREAK; \
    }
#else
    #define CHECK(exp)
#endif