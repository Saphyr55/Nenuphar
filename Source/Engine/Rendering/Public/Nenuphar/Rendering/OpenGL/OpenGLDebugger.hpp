#pragma once

#include "Nenuphar/Core/Core.hpp"

#include <glad/glad.h>

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

#define NP_GL_CHECKER

#ifdef NP_GL_CHECKER
#define NP_GL_CHECK NCHECK(::Nenuphar::OpenGLCheckError(__FUNCTION__, __FILE__, __LINE__) == GL_NO_ERROR)
#else
#define NP_GL_CHECK
#endif

#ifdef NP_GL_CHECKER

#define NP_GL_CHECK_CALL(TOCALL)    \
    ::Nenuphar::OpenGLClearError(); \
    TOCALL;                         \
    NP_GL_CHECK

#define NP_GL_CHECK_RCALL(TOCALL)       \
    [&] {                               \
        ::Nenuphar::OpenGLClearError(); \
        auto res = TOCALL;              \
        NP_GL_CHECK                     \
        return res;                     \
    }()

#else

#define NP_GL_CHECK_CALL(TOCALL) TOCALL;
#define NP_GL_CHECK_RCALL(TOCALL) TOCALL

#endif
