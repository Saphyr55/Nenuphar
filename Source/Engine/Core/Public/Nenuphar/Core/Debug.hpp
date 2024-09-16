#pragma once


#define NP_STATIC_ASSERT(expr) static_assert(expr)


#if defined(_DEBUG) || defined(DEBUG)
    #define NDEBUG
#endif


#if defined(_MSC_VER)
    #define NP_DEBUGBREAK() __debugbreak()
#else
    #define NP_DEBUGBREAK() __builtin_trap()
#endif


#ifdef NDEBUG
    #define NCHECK(expr)      \
        if (!(expr))          \
        {                    \
            NP_DEBUGBREAK(); \
        }
#else
    #define NCHECK(expr)
#endif
