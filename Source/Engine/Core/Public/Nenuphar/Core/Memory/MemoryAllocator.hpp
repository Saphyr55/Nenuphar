#pragma once

#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{
    /**
     * @brief 
     * 
     */
    typedef void* MemoryBlock;

    /**
     * @brief 
     * 
     * @param size 
     * @return MemoryBlock 
     */
    MemoryBlock AllocateMemory(std::size_t size);

    /**
     * @brief 
     * 
     * @param block 
     */
    void FreeMemory(MemoryBlock block);

    /**
     * @brief 
     * 
     * @param destination 
     * @param value 
     * @param size 
     * @return MemoryBlock 
     */
    MemoryBlock WriteMemory(MemoryBlock destination, Int value, std::size_t size);
    
    /**
     * @brief 
     * 
     * @param destination 
     * @param source 
     * @param size 
     * @return MemoryBlock 
     */
    MemoryBlock CopyMemory(MemoryBlock destination,
                           const MemoryBlock source,
                           std::size_t size);


}// namespace Nenuphar