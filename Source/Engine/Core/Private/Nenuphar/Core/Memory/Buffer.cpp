#include "Nenuphar/Core/Memory/Buffer.hpp"
#include "Nenuphar/Core/Debug.hpp"
#include "Nenuphar/Core/Memory/MemoryAllocator.hpp"

namespace Nenuphar
{

    MemoryBlock Buffer::Read(std::size_t size, size_t offset)
    {
        NCHECK(m_data && offset + size <= m_size)
        MemoryBlock source = static_cast<Word*>(m_data) + offset;
        MemoryBlock destination;
        CopyMemory(destination, source, size);
        return destination;
    }

    void Buffer::Write(const MemoryBlock data, std::size_t size, std::size_t offset)
    {
        NCHECK(m_data && offset + size <= m_size)
        MemoryBlock destination = static_cast<Word*>(m_data) + offset;
        CopyMemory(destination, data, size);
    }

    Buffer::Buffer(std::size_t size)
        : m_size(size)
    {
        m_data = AllocateMemory(size);
        m_data = WriteMemory(m_data, Word(0), size);
    }

    Buffer::~Buffer()
    {
        if (m_data)
        {
            FreeMemory(m_data);
        }
    }

}// namespace Nenuphar
