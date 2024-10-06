#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Core/Engine.hpp"
#include "Nenuphar/Core/Logger/Logger.hpp"
#include "Nenuphar/Core/LoopEngine.hpp"
#include "glad/glad.h"
#include <cstdlib>
#include <string>


namespace Nenuphar
{

    void GLAPIENTRY OpenGLMessageCallback(GLenum source,
                                          GLenum type,
                                          GLuint id,
                                          GLenum severity,
                                          GLsizei length,
                                          const GLchar* message,
                                          const void* userParam)
    {

        // ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        {
            return;
        }

        std::string betterSource;
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
                betterSource = "API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                betterSource = "Window System";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                betterSource = "Shader Compiler";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                betterSource = "Third Party";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                betterSource = "Application";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                betterSource = "Other";
                break;
        }

        std::string betterType;
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
                betterType = "Error";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                betterType = "Deprecated Behaviour";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                betterType = "Undefined Behaviour";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                betterType = "Portability";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                betterType = "Performance";
                break;
            case GL_DEBUG_TYPE_MARKER:
                betterType = "Marker";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                betterType = "Push Group";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                betterType = "Pop Group";
                break;
            case GL_DEBUG_TYPE_OTHER:
                betterType = "Other";
                break;
        }

        std::string betterSeverity;
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
                betterSeverity = "High";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                betterSeverity = "Medium";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                betterSeverity = "Low";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                betterSeverity = "Notification";
                break;
        }

        NP_ERROR(OpenGLMessageCallback, "OpenGL [{}-{}] - Information from {} of type {}",
                 betterSeverity, id, betterSource, betterType);
        NP_ERROR(OpenGLMessageCallback, "OpenGL [{}-{}] - {}",
                 betterSeverity, id, message);


    }

    void OpenGLInitDebugger()
    {
        OpenGLEnableDebug();
        OpenGLEnableDebugSynchronize();
        glDebugMessageCallback(&OpenGLMessageCallback, nullptr);
        glDebugMessageControl(GL_DEBUG_SOURCE_API,
                              GL_DEBUG_TYPE_ERROR,
                              GL_DEBUG_SEVERITY_HIGH,
                              0,
                              nullptr,
                              GL_TRUE);
    }

    void OpenGLDisableDebug()
    {
        glDisable(GL_DEBUG_OUTPUT);
    }

    void OpenGLDisableDebugSynchronize()
    {
        glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }

    void OpenGLEnableDebug()
    {
        glEnable(GL_DEBUG_OUTPUT);
    }

    void OpenGLEnableDebugSynchronize()
    {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }

    GLenum OpenGLCheckError(std::string_view functionName,
                            std::string_view fileName,
                            int line)
    {
        GLenum errorCode = 0;
        while ((errorCode = glGetError()) != GL_NO_ERROR && !Engine::IsFinish)
        {
            std::string error;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:
                    error = "INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    error = "STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    error = "STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "INVALID_FRAMEBUFFER_OPERATION";
                    break;
            }
            NP_ERROR(OpenGLCheckError, "[L{}] - Error '{}' at '{}'", line, error, fileName.data());
            NP_ERROR(OpenGLCheckError, "[L{}] - Error in '{}'", line, functionName.data());
        }

        return errorCode;
    }

    void OpenGLClearError()
    {
        while ((glGetError() != GL_NO_ERROR) && !Engine::IsFinish);
    }

}// namespace Nenuphar
