#pragma once

#include "glad/glad.h"
#include <string_view>

namespace Nenuphar
{

    void OpenGLClearError();
    
    GLenum OpenGLCheckError(std::string_view functionName,
                            std::string_view fileName,
                            int line);

    void GLAPIENTRY OpenGLMessageCallback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam);

    void OpenGLInitDebugger();

    void OpenGLDisableDebug();

    void OpenGLDisableDebugSynchronize();

    void OpenGLEnableDebug();

    void OpenGLEnableDebugSynchronize();

} // namespace Nenuphar

#define NPGL_CHECKER

#ifdef NPGL_CHECKER
#define NPOGL_CHECK CHECK(::Nenuphar::OpenGLCheckError(__FUNCTION__, __FILE__, __LINE__) == GL_NO_ERROR)
#else
#define NPOGL_CHECK
#endif

#ifdef NPGL_CHECKER

#define NPOGL_CHECK_CALL(TOCALL)    \
    ::Nenuphar::OpenGLClearError(); \
    TOCALL;                         \
    NPOGL_CHECK

#define NPOGL_CHECK_RCALL(TOCALL)       \
    [&] {                               \
        ::Nenuphar::OpenGLClearError(); \
        auto res = TOCALL;              \
        NPOGL_CHECK                     \
        return res;                     \
    }()

#else

#define NPOGL_CHECK_CALL(TOCALL) TOCALL
#define NPOGL_CHECK_RCALL(TOCALL) TOCALL

#endif
