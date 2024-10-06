#pragma once

#include "Nenuphar/Common/Type/Type.hpp"
#include "Nenuphar/Rendering/RenderBuffer.hpp"

#include <fmt/core.h>
#include <glad/glad.h>

namespace Nenuphar
{

    using OpenGLBufferHandle = UInt;

    class OpenGLImmutableBuffer : public RenderBuffer
    {
    public:
        static SharedRef<OpenGLImmutableBuffer> Create(std::size_t size, const void* data);

        template<typename T>
        static SharedRef<OpenGLImmutableBuffer> Create(const std::vector<T>& data);

        void Initialize();
        
        virtual void Destroy() override;

        void SetBufferStorage(std::size_t size, const void* data, GLbitfield flags) const;

        template<typename T>
        void SetBufferStorage(const std::vector<T>& data, GLbitfield flags) const;

        OpenGLBufferHandle GetHandle() const;

    public:
        OpenGLImmutableBuffer();

        virtual ~OpenGLImmutableBuffer() = default;
    
    private:
        OpenGLBufferHandle m_handle;
    };

    template<typename T>
    void OpenGLImmutableBuffer::SetBufferStorage(const std::vector<T>& data, GLbitfield flags) const
    {
        SetBufferStorage(data.size() * sizeof(T), data.data(), flags);
    }

    template<typename T>
    SharedRef<OpenGLImmutableBuffer> OpenGLImmutableBuffer::Create(const std::vector<T>& data)
    {
        return Create(data.size() * sizeof(T), data.data());
    }

}// namespace Nenuphar
