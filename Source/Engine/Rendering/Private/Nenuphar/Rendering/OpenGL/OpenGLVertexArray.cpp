
#include "Nenuphar/Rendering/OpenGL/OpenGLVertexArray.hpp"
#include "Nenuphar/Common/Instanciate.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLLayoutBuffer.hpp"

#include <glad/glad.h>

namespace Nenuphar
{
    
    OpenGLVertexArray::~OpenGLVertexArray()
    {
    }

    SharedRef<OpenGLVertexArray> OpenGLVertexArray::Create(OpenGLBufferHandle vbo, OpenGLBufferHandle ebo)
    {
        auto vao = MakeSharedRef<OpenGLVertexArray>();
        vao->Initialize();
        vao->LinkElementBuffer(vbo, ebo);
        return vao;
    }

    void OpenGLVertexArray::Initialize()
    {
        NP_GL_CHECK_CALL(glCreateVertexArrays(1, &m_handle))
    }

    void OpenGLVertexArray::Destroy()
    {
        NP_GL_CHECK_CALL(glDeleteVertexArrays(1, &m_handle))
    }

    void OpenGLVertexArray::Bind() const
    {
        NP_GL_CHECK_CALL(glBindVertexArray(m_handle))
    }

    void OpenGLVertexArray::LinkElementBuffer(OpenGLBufferHandle vbo, OpenGLBufferHandle ebo)
    {
        Int bindingIndex = 0;

        for (auto& layout: GLayoutVertex)
        {
            NP_GL_CHECK_CALL(glEnableVertexArrayAttrib(m_handle, layout.Index))
            NP_GL_CHECK_CALL(glVertexArrayAttribBinding(m_handle, layout.Index, bindingIndex));
            NP_GL_CHECK_CALL(glVertexArrayAttribFormat(m_handle, layout.Index, layout.Size, layout.Type, layout.Normalized, layout.Offset));
        }

        UInt offset = 0;
        UInt stride = GLayoutVertex.back().Stride;

        NP_GL_CHECK_CALL(glVertexArrayVertexBuffer(m_handle, bindingIndex, vbo, offset, stride))
        NP_GL_CHECK_CALL(glVertexArrayElementBuffer(m_handle, ebo))
    }

}// namespace Nenuphar
