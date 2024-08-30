#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLDebugger.hpp"

namespace Nenuphar
{

    using VertexArrayId = UInt32;

    class OpenGLVertexArray
    {

    public:

        [[nodiscard]] inline VertexArrayId GetID() const  { return m_vertexArrayId;  }

        void Bind() const;

        void Unbind() const;

        OpenGLVertexArray();
        ~OpenGLVertexArray();

    private:
        VertexArrayId m_vertexArrayId;
    };


    template<typename T>
    void LinkBuffer(
        const OpenGLBuffer<T, OpenGLBufferTarget::ArrayBuffer>& buffer, 
        const std::vector<LayoutBuffer>& layouts)
    {
        buffer.Bind();
        for (const auto& lb : layouts)
        {
            NP_GL_CHECK_CALL(glVertexAttribPointer(
                    lb.Index,
                    lb.Size,
                    lb.Type,
                    lb.Normalized,
                    lb.Stride,
                    lb.Offset));
            NP_GL_CHECK_CALL(glEnableVertexAttribArray(lb.Index));
        }
        buffer.Unbind();
    }

}
