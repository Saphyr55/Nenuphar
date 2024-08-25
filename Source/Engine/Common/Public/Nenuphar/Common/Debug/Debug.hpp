#pragma once

#include <cassert>

#define NP_ASSERT(exp) assert(exp)

#if defined(_MSC_VER)
    #define CHECK(exp)      \
        if (!exp)           \
        {                   \
        }
#else
    #define CHECK(exp)
#endif

#if defined(_MSC_VER)
    #define DCHECK(exp)      \
        if constexpr (!exp)  \
        {                    \
            __debugbreak();  \
        }
#else
    #define CHECK(exp)
#endif