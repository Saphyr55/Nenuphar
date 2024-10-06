#pragma once

#include "CommandBuffer.hpp"
#include "Nenuphar/Common/Type/Type.hpp"

namespace Nenuphar
{

    enum class RenderCommandQueueType : Word
    {
        None = 0x00,
        Copy = 0x01,
        Compute = 0x02,
        Graphics = 0x04,
        All = Copy | Compute | Graphics
    };

    class CommandQueue
    {
    public:
        virtual void Submit(SharedRef<CommandBuffer> commandBuffer) = 0;

        virtual void Execute() = 0;
    };

}// namespace Nenuphar