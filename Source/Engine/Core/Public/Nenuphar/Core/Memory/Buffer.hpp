#pragma once

#include "Nenuphar/Core/Memory/MemoryAllocator.hpp"

#include <cstddef>
#include <vector>

namespace Nenuphar
{

    class Buffer
    {
    public:
        MemoryBlock Read(std::size_t size, std::size_t offset);
        
        template<typename T>
        inline void Write(std::vector<T> data, std::size_t offset);

        void Write(const MemoryBlock data, std::size_t size, std::size_t offset);

        inline const MemoryBlock GetData() const { return m_data; }

        inline MemoryBlock GetData() { return m_data; }

        inline std::size_t GetSize() const { return m_size; }

    public:
        Buffer(std::size_t size);

        virtual ~Buffer();

    private:
        MemoryBlock m_data;
        std::size_t m_size;
    };

    template<typename T>
    void Buffer::Write(std::vector<T> data, std::size_t offset)
    {
        Write(data.data(), offset);
    }

}// namespace Nenuphar