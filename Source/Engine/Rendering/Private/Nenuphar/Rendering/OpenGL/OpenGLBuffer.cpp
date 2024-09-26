#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

#include <glad/glad.h>

namespace Nenuphar 
{   
    
    SharedRef<OpenGLImmutableBuffer> OpenGLImmutableBuffer::Create(std::size_t size, const void* data)
    {
        SharedRef<OpenGLImmutableBuffer> buffer = MakeSharedRef<OpenGLImmutableBuffer>();
        buffer->Initialize();
        buffer->SetBufferStorage(size, data, 0);
        return buffer;
    }

    OpenGLImmutableBuffer::OpenGLImmutableBuffer()
    {
    }

    void OpenGLImmutableBuffer::SetBufferStorage(std::size_t size, const void* data, GLbitfield flags) const
    {
        NP_GL_CHECK_CALL(glNamedBufferStorage(m_handle, size, data, flags));
    }

    void OpenGLImmutableBuffer::Initialize()
    {
        NP_GL_CHECK_CALL(glCreateBuffers(1, &m_handle));
    }

    void OpenGLImmutableBuffer::Destroy()
    {
        NP_GL_CHECK_CALL(glDeleteBuffers(1, &m_handle));
    }

    OpenGLBufferHandle OpenGLImmutableBuffer::GetHandle() const
    {
        return m_handle;
    }

}