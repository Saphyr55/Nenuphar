#include "Nenuphar/Rendering/OpenGL/OpenGLUniformBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"


namespace Nenuphar
{

    OpenGLUniformBuffer::OpenGLUniformBuffer()
    {
        NP_GL_CHECK_CALL(glGenBuffers(1, &m_uniformBufferBlock));
    }

    OpenGLUniformBuffer::~OpenGLUniformBuffer()
    {
        NP_GL_CHECK_CALL(glDeleteBuffers(1, &m_uniformBufferBlock));
    }

    void OpenGLUniformBuffer::BufferSubData(std::size_t offset,
                                            std::size_t size,
                                            const void* value)
    {
        Bind();
        NP_GL_CHECK_CALL(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, value));
        Unbind();
    }

    void OpenGLUniformBuffer::BufferData(std::size_t size, OpenGLBufferUsage usage)
    {
        Bind();
        NP_GL_CHECK_CALL(glBufferData(GL_UNIFORM_BUFFER, size, NULL, usage));
        Unbind();
    }

    void OpenGLUniformBuffer::BindBufferRange(std::size_t index,
                                              std::size_t offset,
                                              std::size_t size)
    {
        NP_GL_CHECK_CALL(glBindBufferRange(GL_UNIFORM_BUFFER,
                                           index, m_uniformBufferBlock, offset, size));
    }

    void OpenGLUniformBuffer::Bind()
    {
        if (m_isBinded) return;
        m_isBinded = true;
        NP_GL_CHECK_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferBlock));
    }

    void OpenGLUniformBuffer::Unbind()
    {
        if (!m_isBinded) return;
        m_isBinded = false;
        NP_GL_CHECK_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    }

}// namespace Nenuphar