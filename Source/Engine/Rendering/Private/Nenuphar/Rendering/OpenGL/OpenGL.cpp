#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"

namespace Nenuphar
{
    UInt32 CreateShader(UInt32 type)
    {
        return glCreateShader(type);
    }

    void ShaderSource(UInt32 shader, Int count, const Char** source, const Int* length)
    {
        glShaderSource(shader, count, source, length);
    }

    void UseProgram(UInt32 program)
    {
        glUseProgram(program);
    }

    void DeleteShader(UInt32 shader)
    {
        glDeleteShader(shader);
    }

    UInt32 GetUniformLocation(UInt32 program, const char* uniform)
    {
        return glGetUniformLocation(program, uniform);
    }

    void CompileShader(UInt32 shader)
    {
        glCompileShader(shader);
    }

    void LinkProgram(UInt32 program)
    {
        glLinkProgram(program);
    }

    UInt32 CreateProgram()
    {
        return glCreateProgram();
    }

    void SetUniform(Int location, Matrix4f value)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, Matrix4f::ValueArray(value).data());
    }

    void SetUniform(Int location, Vector4f value)
    {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void SetUniform(Int location, Vector3f value)
    {
        glUniform3f(location, value.x, value.y, value.z);
    }

    void SetUniform(Int location, Vector2f value)
    {
        glUniform2f(location, value.x, value.y);
    }

    void SetUniform(Int location, Float value)
    {
        glUniform1f(location, value);
    }

    void SetUniform(Int location, UInt32 value)
    {
        glUniform1ui(location, value);
    }

    void SetUniform(Int location, Int value)
    {
        glUniform1i(location, value);
    }

}