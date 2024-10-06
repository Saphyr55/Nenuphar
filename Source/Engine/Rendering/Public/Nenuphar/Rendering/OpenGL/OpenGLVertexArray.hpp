#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLBuffer.hpp"
#include "Nenuphar/Rendering/RenderHandle.hpp"


namespace Nenuphar
{
    
    using OpenGLVertexArrayHandle = UInt32;
    
    class OpenGLVertexArray : public RenderHandle
    {
    public: 
        static SharedRef<OpenGLVertexArray> Create(OpenGLBufferHandle vbo, OpenGLBufferHandle ebo);

        void Initialize();

        virtual void Destroy() override;

        void Bind() const;

        void LinkElementBuffer(OpenGLBufferHandle vbo, OpenGLBufferHandle ebo);        

        inline OpenGLVertexArrayHandle GetHandle() const { return m_handle;  }
        
        OpenGLVertexArray() = default;
        ~OpenGLVertexArray();

    private:
        OpenGLVertexArrayHandle m_handle;
    };



}
