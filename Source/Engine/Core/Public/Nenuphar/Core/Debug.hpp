#pragma once


#define NP_SASSERT(exp) static_assert(exp)


#if defined(_DEBUG) || defined(DEBUG)
    #define NDEBUG
#endif


#if defined(_MSC_VER)
    #define NP_DEBUGBREAK() __debugbreak()
#else
    #define NP_DEBUGBREAK() __builtin_trap()
#endif


#ifdef NDEBUG
    #define NCHECK(exp)      \
        if (!(exp))          \
        {                    \
            NP_DEBUGBREAK(); \
        }
#else
    #define CHECK(exp)
#endif
