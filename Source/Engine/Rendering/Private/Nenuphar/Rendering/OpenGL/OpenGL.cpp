#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

namespace Nenuphar
{
    UInt32 CreateShader(UInt32 type)
    {
        return NP_GL_CHECK_RCALL(glCreateShader(type));
    }

    void ShaderSource(UInt32 shader, Int count, const Char** source, const Int* length)
    {
        NP_GL_CHECK_CALL(glShaderSource(shader, count, source, length));
    }

    void UseProgram(UInt32 program)
    {
        NP_GL_CHECK_CALL(glUseProgram(program));
    }

    void DeleteShader(UInt32 shader)
    {
        NP_GL_CHECK_CALL(glDeleteShader(shader));
    }

    UInt32 GetUniformLocation(UInt32 program, const char* uniform)
    {
        return NP_GL_CHECK_RCALL(glGetUniformLocation(program, uniform));
    }

    void CompileShader(UInt32 shader)
    {
        NP_GL_CHECK_CALL(glCompileShader(shader));
    }

    void LinkProgram(UInt32 program)
    {
        NP_GL_CHECK_CALL(glLinkProgram(program));
    }

    UInt32 CreateProgram()
    {
        return NP_GL_CHECK_RCALL(glCreateProgram());
    }

    void DeleteProgram(UInt32 program)
    {
        NP_GL_CHECK_CALL(glDeleteProgram(program));
    }

    void SetUniform(Int location, Matrix4f value)
    {
        NP_GL_CHECK_CALL(glUniformMatrix4fv(
                location,
                1,
                GL_FALSE,
                Matrix4f::ValueArray(value).data()
                ));
    }

    void SetUniform(Int location, Vector4f value)
    {
        NP_GL_CHECK_CALL(glUniform4f(location, value.x, value.y, value.z, value.w));
    }

    void SetUniform(Int location, Vector3f value)
    {
        NP_GL_CHECK_CALL(glUniform3f(location, value.x, value.y, value.z));
    }

    void SetUniform(Int location, Vector2f value)
    {
        NP_GL_CHECK_CALL(glUniform2f(location, value.x, value.y));
    }

    void SetUniform(Int location, Float value)
    {
        NP_GL_CHECK_CALL(glUniform1f(location, value));
    }

    void SetUniform(Int location, UInt32 value)
    {
        NP_GL_CHECK_CALL(glUniform1ui(location, value));
    }

    void SetUniform(Int location, Int value)
    {
        NP_GL_CHECK_CALL(glUniform1i(location, value));
    }

}