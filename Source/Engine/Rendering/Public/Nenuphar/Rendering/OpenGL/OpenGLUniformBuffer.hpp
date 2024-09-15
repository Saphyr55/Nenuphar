#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGLShader.hpp"
#include "Nenuphar/Rendering/UniformBuffer.hpp"
#include <cstddef>

namespace Nenuphar
{

    class OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        void BufferSubData(std::size_t offset, std::size_t size, const void* value);

        void BufferData(std::size_t size, OpenGLBufferUsage usage);
        
        void BindBufferRange(std::size_t index,
                             std::size_t offset,
                             std::size_t size);

        void Bind();
        void Unbind();

        OpenGLUniformBuffer();
        virtual ~OpenGLUniformBuffer();

    private:
        UInt m_uniformBufferBlock;
    };

}// namespace Nenuphar