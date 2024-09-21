#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "glad/glad.h"

namespace Nenuphar 
{   
    
    SharedRef<OpenGLImmutableBuffer> OpenGLImmutableBuffer::Create(std::size_t size, const void* data)
    {
        SharedRef<OpenGLImmutableBuffer> buffer = MakeSharedRef<OpenGLImmutableBuffer>(true);
        buffer->SetBufferStorage(size, data, 0);
        return buffer;
    }

    OpenGLImmutableBuffer::OpenGLImmutableBuffer(Bool init)
        : m_isInit(false), m_isDestroy(false)
    {
        if (init)
        {
            Initialize();
        }
    }

    void OpenGLImmutableBuffer::SetBufferStorage(std::size_t size, const void* data, GLbitfield flags) const
    {
        NCHECK(!m_isDestroy && m_isInit)
        NP_GL_CHECK_CALL(glNamedBufferStorage(m_handle, size, data, flags));
    }

    void OpenGLImmutableBuffer::Initialize()
    {
        if (m_isInit) return;
        NP_GL_CHECK_CALL(glCreateBuffers(1, &m_handle));
        m_isInit = true;
    }

    void OpenGLImmutableBuffer::Destroy()
    {
        if (m_isDestroy) return;
        NP_GL_CHECK_CALL(glDeleteBuffers(1, &m_handle));
        m_isDestroy = true;
    }

    OpenGLBufferHandle OpenGLImmutableBuffer::GetHandle() const
    {
        return m_handle;
    }

}