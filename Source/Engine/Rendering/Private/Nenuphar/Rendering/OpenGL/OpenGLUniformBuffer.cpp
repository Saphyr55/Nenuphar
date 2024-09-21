#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

#include <glad/glad.h>


namespace Nenuphar
{

    UInt OpenGL_GetUniformBlock(SharedRef<Shader> program,
                                const char* uniformBlockName)
    {
        return NP_GL_CHECK_RCALL(glGetUniformBlockIndex(program->Id(), uniformBlockName));
    }

    OpenGLUniformBuffer::OpenGLUniformBuffer(std::size_t size)
        : m_size(size)
    {
        NP_GL_CHECK_CALL(glCreateBuffers(1, &m_uniformBuffer));
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        NP_GL_CHECK_CALL(glDeleteBuffers(1, &m_uniformBuffer));
    }

    void OpenGLUniformBuffer::BufferSubData(std::size_t offset,
                                            std::size_t size,
                                            const void* value)
    {
        NP_GL_CHECK_CALL(glNamedBufferSubData(m_uniformBuffer, offset, size, value));
    }

    void OpenGLUniformBuffer::BufferData(const void* data, OpenGLBufferUsage usage)
    {
        NP_GL_CHECK_CALL(glNamedBufferData(m_uniformBuffer, m_size, data, usage));
    }   

    void OpenGLUniformBuffer::BindBufferBase(std::size_t index)
    {
        NP_GL_CHECK_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, index, m_uniformBuffer));
    }

    void OpenGLUniformBuffer::Bind()
    {
        NP_GL_CHECK_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer));
    }

    void OpenGLUniformBuffer::Unbind()
    {
        NP_GL_CHECK_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    }

}// namespace Nenuphar