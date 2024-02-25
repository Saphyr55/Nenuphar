#pragma once

#include "Nenuphar/Common/Common.hpp"
#include "Nenuphar/Graphics/OpenGL/Buffer.hpp"

namespace Nenuphar
{

    using VertexArrayID = UInt;

    class VertexArray final
    {

    public:

        [[nodiscard]] inline VertexArrayID GetID() const 
        { 
            return m_vertexArrayID; 
        }

        void Bind() const;

        void Unbind() const;

        VertexArray();
        ~VertexArray();

    private:
        VertexArrayID m_vertexArrayID;
    };


    template<typename T>
    void LinkBuffer(
        const OpenGLBuffer<T, OpenGLBufferTarget::ArrayBuffer>& buffer, 
        const std::vector<LayoutBuffer>& layouts)
    {
        buffer.Bind();
        for (const auto& lb : layouts) {
            glVertexAttribPointer(lb.Index, lb.Size, lb.Type, lb.Stride, lb.Offset, lb.Normalized);
            glEnableVertexAttribArray(lb.Index);
        }
        buffer.Unbind();
    }

}
