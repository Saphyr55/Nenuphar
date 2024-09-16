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
        void BufferData(std::size_t size, OpenGLBufferUsage usage);
        
        /**
         * @brief 
         * 
         * @param index 
         * @param offset 
         * @param size 
         */
        void BindBufferRange(std::size_t index,
                             std::size_t offset,
                             std::size_t size);
        
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
    
    public:
        /**
         * @brief Construct a OpenGL Uniform Buffer object
         * 
         */
        OpenGLUniformBuffer();

        /**
         * @brief Destroy the Uniform Buffer object
         * 
         */
        virtual ~OpenGLUniformBuffer();

    private:
        bool m_isBinded;
        UInt m_uniformBufferBlock;
    };

}// namespace Nenuphar