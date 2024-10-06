#include "Nenuphar/Core/Memory/MemoryAllocator.hpp"

#include <cstdlib>
#include <cstring>

namespace Nenuphar 
{

    MemoryBlock AllocateMemory(std::size_t size)
    {
        return std::malloc(size);
    }

    void FreeMemory(MemoryBlock block)
    {
        std::free(block);
    } 

    MemoryBlock CopyMemory(MemoryBlock destination, const MemoryBlock source, std::size_t size)
    {
        return std::memcpy(destination, source, size);
    }

    MemoryBlock WriteMemory(MemoryBlock destination, Int value, std::size_t size)
    {
        return std::memset(destination, value, size);
    }

}