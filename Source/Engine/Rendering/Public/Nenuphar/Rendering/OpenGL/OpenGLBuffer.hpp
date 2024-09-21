#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

#include <fmt/core.h>
#include <glad/glad.h>

namespace Nenuphar
{

    using OpenGLBufferHandle = UInt;

    class OpenGLImmutableBuffer
	{
	public:
        static SharedRef<OpenGLImmutableBuffer> Create(std::size_t size, const void* data);

        template<typename T>
        static SharedRef<OpenGLImmutableBuffer> Create(std::vector<T>& data);

        void Initialize();

        void Destroy();
        
        void SetBufferStorage(std::size_t size, const void* data, GLbitfield flags) const;
        
        OpenGLBufferHandle GetHandle() const;

    public:
        OpenGLImmutableBuffer(Bool init = false);

        virtual ~OpenGLImmutableBuffer() = default;

    protected:
        OpenGLBufferHandle m_handle;

    private:
        Bool m_isInit;
        Bool m_isDestroy;
    };

    template<typename T>
    SharedRef<OpenGLImmutableBuffer> OpenGLImmutableBuffer::Create(std::vector<T>& data)
    {
        return Create(data.size() * sizeof(T), data.data());
    }
    
}
