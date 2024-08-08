#pragma once

#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"

namespace Nenuphar
{

    using VertexArrayID = UInt;

    class OpenGLVertexArray
    {

    public:

        [[nodiscard]] inline VertexArrayID GetID() const  { return m_vertexArrayID;  }

        void Bind() const;

        void Unbind() const;

        OpenGLVertexArray();
        ~OpenGLVertexArray();

    private:
        VertexArrayID m_vertexArrayID;
    };


    template<typename T>
    void LinkBuffer(
        const OpenGLBuffer<T, OpenGLBufferTarget::ArrayBuffer>& buffer, 
        const std::vector<LayoutBuffer>& layouts)
    {
        buffer.Bind();
        for (const auto& lb : layouts)
        {
            glVertexAttribPointer(lb.Index, lb.Size, lb.Type, lb.Normalized, lb.Stride, lb.Offset);
            glEnableVertexAttribArray(lb.Index);
        }
        buffer.Unbind();
    }

}
