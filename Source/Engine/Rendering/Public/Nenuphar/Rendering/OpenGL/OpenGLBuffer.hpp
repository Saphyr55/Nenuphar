#pragma once

#include <variant>
#include <vector>

#include <fmt/core.h>
#include <glad/glad.h>

#include "Nenuphar/Rendering/OpenGL/Vertex.hpp"
#include "Nenuphar/Rendering/OpenGL/OpenGL.hpp"


namespace Nenuphar
{

    using OpenGLBufferID = UInt;

    template<typename T, OpenGLBufferTarget bt>
    class OpenGLBuffer final
	{
	public:

		void Bind() const;

		OpenGLBufferUsage Usage() const;

		OpenGLBufferID GetID() const;

		void Unbind() const;

		explicit OpenGLBuffer(const std::vector<T>& data, OpenGLBufferUsage usage = OpenGLBufferUsage::StaticDraw);
        ~OpenGLBuffer();

	private:
		OpenGLBufferUsage m_usage;
		OpenGLBufferID m_bufferID;
    };

	template<typename T, OpenGLBufferTarget bt>
    OpenGLBuffer<T, bt>::~OpenGLBuffer() 
    { 
        glDeleteBuffers(1, &m_bufferID); 
    }

	template<typename T, OpenGLBufferTarget bt>
    OpenGLBuffer<T, bt>::OpenGLBuffer(const std::vector<T>& data, OpenGLBufferUsage usage) 
        : m_usage(usage)
	{
		glGenBuffers(1, &m_bufferID);
		Bind();
		glBufferData(bt, data.size() * sizeof(T), data.data(), usage);
	}
	  
	template<typename T, OpenGLBufferTarget bt>
    inline void OpenGLBuffer<T, bt>::Bind() const 
    { 
        glBindBuffer(bt, m_bufferID);
    }

	template<typename T, OpenGLBufferTarget bt>
    inline void OpenGLBuffer<T, bt>::Unbind() const 
    { 
        glBindBuffer(bt, 0);
    }

	template<typename T, OpenGLBufferTarget bt>
    OpenGLBufferUsage OpenGLBuffer<T, bt>::Usage() const 
    { 
        return m_usage;
    }

	template<typename T, OpenGLBufferTarget bt>
    OpenGLBufferID OpenGLBuffer<T, bt>::GetID() const 
    { 
        return m_bufferID; 
    }

	using OpenGLElementBuffer = OpenGLBuffer<UInt, OpenGLBufferTarget::ElementArrayBuffer>;
	using OpenGLVertexBuffer = OpenGLBuffer<Vertex, OpenGLBufferTarget::ArrayBuffer>;

}
