#pragma once

#define NpSASSERT(exp) static_assert(exp)

#if defined(_MSC_VER)
    #define NP_DEBUGBREAK() __debugbreak()
#else
    #define NP_DEBUGBREAK() __builtin_trap()
#endif


#if defined(_DEBUG) || defined(DEBUG)
#define CHECK(exp)       \
    if (!(exp))          \
    {                    \
        NP_DEBUGBREAK();  \
    }
#else
    #define CHECK(exp)
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define CCHECK(exp)     \
    if constexpr (!(exp)) \
    {                   \
        NP_DEBUGBREAK(); \
    }
#else
    #define CHECK(exp)
#endif