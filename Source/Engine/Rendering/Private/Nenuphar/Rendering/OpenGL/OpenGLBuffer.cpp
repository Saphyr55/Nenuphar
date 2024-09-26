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
        SharedRef<OpenGLImmutableBuffer> buffer = MakeSharedRef<OpenGLImmutableBuffer>();
        buffer->Initialize();
        buffer->SetBufferStorage(size, data, GL_DYNAMIC_STORAGE_BIT);
        return buffer;
    }

    OpenGLImmutableBuffer::OpenGLImmutableBuffer()
        : m_isInit(false), m_isDestroy(false)
    {
    }

    void OpenGLImmutableBuffer::SetBufferStorage(std::size_t size, const void* data, GLbitfield flags) const
    {
        NCHECK(!m_isDestroy && m_isInit)
        NP_GL_CHECK_CALL(glNamedBufferStorage(m_handle, size, data, flags));
    }

    void OpenGLImmutableBuffer::Initialize()
    {
        if (m_isInit) return;
        m_isInit = true;

        NP_GL_CHECK_CALL(glCreateBuffers(1, &m_handle));
    }

    void OpenGLImmutableBuffer::Destroy()
    {
        if (m_isDestroy) return;
        m_isDestroy = true;

        NP_GL_CHECK_CALL(glDeleteBuffers(1, &m_handle));
    }

    OpenGLBufferHandle OpenGLImmutableBuffer::GetHandle() const
    {
        return m_handle;
    }

}