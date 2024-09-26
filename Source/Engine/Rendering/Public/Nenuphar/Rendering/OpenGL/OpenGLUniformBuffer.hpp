#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"
#include "Nenuphar/Rendering/RenderBuffer.hpp"
#include "Nenuphar/Rendering/Shader.hpp"


namespace Nenuphar
{

    UInt OpenGL_GetUniformBlock(SharedRef<Shader> program,
                                const char* uniformBlockName);


    class OpenGLUniformBuffer : public RenderBuffer
    {
    public:
        /**
         * @brief 
         * 
         * @param offset 
         * @param size 
         * @param value 
         */
        void BufferSubData(std::size_t offset, std::size_t size, const void* value);

        /**
         * @brief 
         * 
         * @param size 
         * @param usage 
         */
        void BufferData(const void* data, OpenGLBufferUsage usage);

        /**
         * @brief 
         * 
         * @param index 
         */
        void BindBufferBase(std::size_t index);

        /**
         * @brief 
         * 
         */
        void Bind();

        /**
         * @brief 
         * 
         */
        void Unbind();

        /**
         * @brief 
         * 
         */
        virtual void Destroy() override;

    public:
        /**
         * @brief Construct a OpenGL Uniform Buffer object
         * 
         * @param size-The buffer size.
         */
        OpenGLUniformBuffer(std::size_t size);

        /**
         * @brief Destroy the Uniform Buffer object
         * 
         */
        ~OpenGLUniformBuffer();

    private:
        std::size_t m_size;
        UInt m_uniformBuffer;
    };

}// namespace Nenuphar